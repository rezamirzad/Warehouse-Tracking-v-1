
// Project LUNA Access Point

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266TrueRandom.h>

// Defining a static IP address: local & gateway
IPAddress    apIP(29, 7, 20, 18);  

/* This are the WiFi access point settings. Update them to your likin */
const char *ssid = "";
const char *password = "";

// Define a web server at port 80 for HTTP  
  ESP8266WebServer server(80);
// UUID holders LONG INT
  unsigned long int uuidInt[20];
  unsigned long int equivalentID[200];

// UUID holders CHAR
  char uuidChar[20][15];

// UUID holders STRING
  String uuidString[10];

// URL arguments
  String argPlace="";
  String argPalette="";

// Test vars  
  char s1[10];
  char s2[10];
  int counter = 0;

// UUID to PalletNumber
  
  

void handleRoot() {
  counter++;
  simRandomID();
// URL arguments
  String argPlace="";
  String argPalette="";
  
  int placeNumber;
  unsigned long int palletNumber;
  
  digitalWrite (LED_BUILTIN, 0); //turn the built in LED on pin DO of NodeMCU on
  
// URL Inputs
  argPlace += server.argName(0);      //Get the name of the place
  argPalette +=server.arg(0);         //Get the name of the pallet

  
  placeNumber = argPlace.toInt();
  //palletNumber = argPalette.toInt();
  //uuidInt[placeNumber-1] = palletNumber;
  
  //uuidString[placeNumber-1] = String (uuidInt[placeNumber-1]);
  //uuidString[placeNumber-1].toCharArray(uuidChar[placeNumber-1],15);
  argPalette.toCharArray(uuidChar[placeNumber-1],15);
  uuidInt[placeNumber-1] = argPalette.toInt();
  assignPalletNumber();
 
    

//Value for strings
      
// Random UUID
  unsigned long int uuid1, uuid2, uuid3, uuid4;
  
  
// Server up-time counter
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  
// HTML page builder
  char html[1500];

// Build an HTML page to display on the web-server root address
  snprintf ( html, 1500,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='15'/>\
    <title>Project LUNA WiFi Network</title>\
    <style>\
      body { background-color: #cccccc; font-family: Courier; font-size: 1.5em; Color: #000000; }\
      h1 { Color: #AA0000; }\
    </style>\
  </head>\
  <body>\
    <h1>Project LUNA</h1>\ 
    <h2> Access Point and Web Server Demo</h2>\
    <p>By: Reza MIRZAD (reza.mirzad@gmail.com)</p>\
    <p>Server uptime: %02d:%02d:%02d</p>\
    <p> </p>\
    <p> </p>\
    <p>Emplacement 01:   %03d <p>\
    <p>Emplacement 02:   %03d <p>\
    <p>Emplacement 03:   %03d (Simulated)<p>\
    <p>Emplacement 04:   %03d (Simulated)<p>\
    <p>Emplacement 05:   %03d (Simulated)<p>\
    <p>Emplacement 06:   %03d (Simulated)<p>\
    <p>Emplacement 07:   %03d (Simulated)<p>\
    <p>Emplacement 08:   %03d (Simulated)<p>\
    <p>Emplacement 09:   %03d (Simulated)<p>\
    <p>Emplacement 10:   %03d (Simulated)<p>\
    <p>Emplacement 11:   %03d (Simulated)<p>\
    <p>Emplacement 12:   %03d (Simulated)<p>\
    <p>Emplacement 13:   %03d (Simulated)<p>\
    <p>Emplacement 14:   %03d (Simulated)<p>\
    <p>Emplacement 15:   %03d (Simulated)<p>\
    <p>Emplacement 16:   %03d (Simulated)<p>\
    <p>Emplacement 17:   %03d (Simulated)<p>\
    <p>Emplacement 18:   %03d (Simulated)<p>\
    <p>Emplacement 19:   %03d (Simulated)<p>\
    <p>Emplacement 20:   %03d (Simulated)<p>\
    <p><small>This page refreshes every 15 seconds.<p>\
    <p>Click <a href=\"javascript:window.location.reload();\">here</a> to refresh the page now.</small></p>\
  </body>\
</html>",

    hr, min % 60, sec % 60,
    uuidInt[0], uuidInt[1], 
    uuidInt[2], uuidInt[3], uuidInt[4], uuidInt[5], uuidInt[6],
    uuidInt[7], uuidInt[8], uuidInt[9], uuidInt[10], uuidInt[11],
    uuidInt[12], uuidInt[13], uuidInt[14], uuidInt[15], uuidInt[16],
    uuidInt[17], uuidInt[18], uuidInt[19]     
  );

// Send HTML to web server
  server.send ( 200, "text/html", html );
  digitalWrite ( LED_BUILTIN, 1 );
}

void handleNotFound() {
  digitalWrite ( LED_BUILTIN, 0 );
  String message = "Project LUNA File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i=0; i<server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  digitalWrite ( LED_BUILTIN, 1 ); //turn the built in LED on pin DO of NodeMCU off
}
void assignPalletID() {
  equivalentID[0] = 1440675266;
  equivalentID[1] = 1704568889;
  equivalentID[2] = 1035899218;
  equivalentID[3] = 2147483647;
  equivalentID[4] = 54671547;
  for ( int i=5; i<150; i++ ) {
    equivalentID[i] = i+1;  
  }
  for ( int i=150; i<200; i++ ) {
    equivalentID[i] = 0;  
  }
}
void simRandomID(){
  int randomExecution;
  int randomNum, randomNum2;
  randomNum = ESP8266TrueRandom.random(18)+2;
  randomNum2 = ESP8266TrueRandom.random(15)+5;
  randomExecution = ESP8266TrueRandom.random(5);
  if (randomExecution == 3){
    for (int i=5; i<200; i++){
      randomNum2 = ESP8266TrueRandom.random(25)+5;
      unsigned long int temp = equivalentID[randomNum2];
      equivalentID[randomNum2] = equivalentID[i];
      equivalentID[i] = temp;
    }
    for (int i=2; i<20; i++){
      uuidInt[i] = equivalentID[i+5];
    }  
  }
}

void assignPalletNumber(){
  for (int i=0; i<5; i++){
    if (uuidInt[0]==equivalentID[i])
      uuidInt[0]=i+1;
    if (uuidInt[1]==equivalentID[i])
      uuidInt[1]=i+1;
  }
}
void setup() {
//  pinMode ( ledPin, OUTPUT );
  //digitalWrite ( ledPin, 0 );
  for ( int i=0; i<20; i++ )
    strcpy(uuidChar[i],"Empty");
  delay(1000);
  Serial.begin(115200);
 
  
  Serial.println();
  Serial.println("Configuring access point...");

  //set-up the custom IP address
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("Luna Access Point IP address: ");
  Serial.println(myIP);
  
  server.on ( "/", handleRoot );
  server.on ( "/place", handleRoot);

  server.onNotFound ( handleNotFound );
  
  server.begin();
  Serial.println("HTTP server started");
  Serial.print("IP:   ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:  ");     Serial.println(WiFi.softAPmacAddress());
  Serial.println("Listening");
  assignPalletID();
  
}

void loop() {
  
  server.handleClient();
}
