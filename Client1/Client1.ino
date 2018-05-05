#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   20
#define SS_PIN    2
#define place     1

MFRC522 mfrc522(SS_PIN, RST_PIN);

bool rfid_present_p = false;
bool rfid_present = false;
int rfid_error_counter = 0;
bool tag_found = false;

unsigned long getID(){
  
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte [0] << 24;
  hex_num += mfrc522.uid.uidByte [1] << 16;
  hex_num += mfrc522.uid.uidByte [2] <<  8;
  hex_num += mfrc522.uid.uidByte [3];

  return hex_num;  
}


void setup() {
  Serial.begin(115200);
  while (!Serial);
  SPI.begin();
  // Initialize MFRC522 tag reader 
  mfrc522.PCD_Init();
  // Enhance the MFRC522 Receiver Gain to maximum value of 48 dB
  mfrc522.PCD_SetRegisterBitMask(mfrc522.RFCfgReg, (0x07<<4));
  
  WiFi.begin("ProjectLUNA", "Luna2018");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
  }
  Serial.println("Connected to ProjectLuna network...");


}

void loop() {
  String tag;
  bool changed = false;
  rfid_present_p = rfid_present;
  rfid_error_counter += 1;
  if(rfid_error_counter >2){
    tag_found = false;
  }
  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);
  // Reset baud rates
  mfrc522.PCD_WriteRegister(mfrc522.TxModeReg, 0x00);
  mfrc522.PCD_WriteRegister(mfrc522.RxModeReg, 0x00);
  // Reset ModWidthReg
  mfrc522.PCD_WriteRegister(mfrc522.ModWidthReg, 0x26);
  MFRC522::StatusCode result = mfrc522.PICC_RequestA(bufferATQA, &bufferSize);

  if(result == mfrc522.STATUS_OK){
    if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue   
      return;
    }
    rfid_error_counter = 0;
    tag_found = true;        
  }

  rfid_present = tag_found;

  if (rfid_present && !rfid_present_p){
    Serial.print("Tag found ");
    unsigned long uid = getID();
    tag ="";
    tag += uid;
    Serial.println(tag);
    changed = true;
  }
 if (!rfid_present && rfid_present_p){
    Serial.print("Tag gone ");
    tag = "Empty";
    Serial.println(tag);
    changed = true;
  }
  

  
  if (WiFi.status()==WL_CONNECTED && changed==true){
   HTTPClient http;
   String httpR = "http://29.7.20.18/place?";
   httpR += place;
   httpR +="=";
   //randomPlace = random(1,10);
   //httpR +=randomPlace;
   //httpR +="=";
   httpR +=tag;
   http.begin(httpR);
   http.addHeader("Content-Type", "text/plain");
   int httpCode = http.POST("Place 1");
   http.end();      

   Serial.println(httpR);
   Serial.println("Data sent");
   changed = false;
  }
   //delay(10000);
}
