//Setting UART communication between ESP32 and Arduino uno.
//Master is esp32 (it transmitting data to Arduino Atmega328p).
//choose the BOARD in TOOLS Adafruit esp32 feather.
//when loading up this sketch press on the Arduino's reset button utill uploaded and visa versa.
//Tx pin of Esp32 is connected to the Rx pin oo Arduino uno, both are connected to the common ground.
//upload the program twice open both to open both UART connections
//To open the webpage use the ip address of the computer.



#define RXD2 16
#define TXD2 17


//For wifi connection
#define WIFI_INTERVAL 500
#define WIFI_SSID "#Telia-CDC9A8"
#define WIFI_PASS "a6G&3@e=f7(FCa3H"

#include "WiFifunctions.h"

char uartData;


void setup()
{
    Serial.begin(9800);
    
    initWifi();

    initWebServer();
    
    // The format for setting serial port.
    // serial2.begin(baud-rate,protocol,RX pin ,TXpin);
     
    Serial2.begin(38400,SERIAL_8N1,RXD2 ,TXD2);
   // delay(2000);
   // Serial.println(" --------- Select Notes--------- ");
   // Serial.println(" C  D  E  F  G  A  B &&& P to play ");
}
  
 


void loop()
{
  server.handleClient();
   
}
