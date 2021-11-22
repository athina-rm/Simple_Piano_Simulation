#include <WiFi.h> 
#include <WiFiClient.h>
#include <WebServer.h>  
WebServer server(80);

void initWifi(){
  Serial.println("connecting to wifi");
  WiFi.begin(WIFI_SSID,WIFI_PASS);

  while(WiFi.status() != WL_CONNECTED){
    
    delay(WIFI_INTERVAL);
    Serial.print(".");
    
  }

Serial.println("connected to wifi");
Serial.println("IP Adress:" );
Serial.println(WiFi.localIP());
Serial.println("MAC address: ");
Serial.println(WiFi.macAddress());
}

void read_data(char uartData){        //nessary to have the function in this place, else gives an error: (function not declared) while compile.

 switch(uartData)
        {
        case 'A':
            
            Serial2.write('A') ;
            break;
        case 'B':
            
             Serial2.write('B') ;
            break;
        case 'C':
            
             Serial2.write('C') ;
            break;
        case 'D':
            
             Serial2.write('D') ;
            break;
        case 'E':
            
             Serial2.write('E') ;
            break;
        case 'F':
            
             Serial2.write('F') ;
            break;
        case 'G':
           
             Serial2.write('G') ;
            break;
        case 'P':
            Serial2.write('P') ;
            break;
        }
      // uartData = '\0';
}

void handleWebData(){
   String Receivedtone = server.arg("tone");
  // Serial.println(Receivedtone);
   char receiv_tone = Receivedtone[0];
   Serial.println(receiv_tone);
   read_data(receiv_tone);
   receiv_tone  = '\0';
   
  //send reseived data from webserver to esp32 code

  server.sendHeader("Access-Control-Allow-Methods", "POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  
}

#include "index.h"

void handleIndexPage(){
  String indexPage = index_page;
  server.send(200, "text/html",indexPage);
}

void initWebServer(){
  server.on("/", handleIndexPage);
  server.on("/sound",handleWebData);
  server.begin();
}
