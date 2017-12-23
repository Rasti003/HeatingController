/*
  WeMos D1 Mini   Nokia 5110    Description
  (ESP8266)       PCD8544 LCD
  D2 (GPIO4)      0 RST         Output from ESP to reset display
  D1 (GPIO5)      1 CE          Output from ESP to chip select/enable display
  D6 (GPIO12)     2 DC          Output from display data/command to ESP
  D7 (GPIO13)     3 Din         Output from ESP SPI MOSI to display data input
  D5 (GPIO14)     4 Clk         Output from ESP SPI clock
  3V3             5 Vcc         3.3V from ESP to display
  D0 (GPIO16)     6 BL          3.3V to turn backlight on, or PWM
  G               7 Gnd         Ground
  Dependencies:
  https://github.com/adafruit/Adafruit-GFX-Library
  https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library
  - This pull request adds ESP8266 support:
  - https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library/pull/27
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// pins
const int8_t RST_PIN = D2;
const int8_t CE_PIN = D1;
const int8_t DC_PIN = D6;
const int8_t BL_PIN = D0;

//  wifi
const char* myssid = "Janusz_COMPANY";
const char* mypass = "Kleszczu!@";
//Connection flag
bool isConected = true;
//Server
ESP8266WebServer server(80);
String Argument_Name, Clients_Response1, Clients_Response2;

String  theme = "darkly";
String page = "";
double data;
//Signal strength
long rssi =0;
//value
int fireplaceTMP = 20;
int pumpFireplace = 80;
int hysteresis =10;
static  const  uint8_t ledPin = D3;
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);




void setup(void) {
   pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, HIGH);
  digitalWrite(13, HIGH);
  
  Serial.begin(9600);

  // Set WiFi to station mode and disconnect from an AP if it was previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Turn LCD backlight on
  pinMode(BL_PIN, OUTPUT);
  digitalWrite(BL_PIN, HIGH);

  // Configure LCD
  display.begin();
  display.setContrast(50);  // Adjust for your display
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.clearDisplay();
  Connection();
 // httpServer(rssi);

 digitalWrite(ledPin, LOW);

     server.on("/", [](){
 
  String page = "<!DOCTYPE html>";
          String IPaddress = WiFi.localIP().toString();
page +=  "<html>";
page +=  "<head>";
page +=    "<meta http-equiv='Content-Type' content='text/html; charset=UTF-8' />";
page +=    "<meta name='viewport' content='width=1,initial-scale=1,user-scalable=1' />";
page +=    "<title>Centrum dowodzenia</title>"; 
page +=  "<link href='http://fonts.googleapis.com/css?family=Lato:100italic,100,300italic,300,400italic,400,700italic,700,900italic,900' rel='stylesheet' type='text/css'>";
page +=  "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>";
page +=  "<link rel='stylesheet' href='http://legalnyplener.pl/przemektest/kominek/biblioteki/style.css'/>";
page += "<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>";
page += "<script type='text/javascript' src='https://ajax.googleapis.com/ajax/libs/jquery/1.7.2/jquery.min.js'></script> " ;
page += "<script src='http://legalnyplener.pl/przemektest/kominek/biblioteki/jquery.easypiechart.min.js'></script>";
page += " <script>";
page += "$(function() {";
page +=  " $('.chart').easyPieChart({";
page +=    " easing: 'easeOutBounce',";
page +=    " onStep: function(from, to, percent) {";
page +=      " $(this.el).find('.percent').text(Math.round(percent));";
page +=    " }";
page +=  " });" ; 
page +=  "});";
page +=  "</script>";
page +=  "</head>";
page +=  "<body>";
page += "<body>";
page += "<div style='overflow: hidden'>";
page +=  "<div class='row'>";
page +=    "<div class='col-xs-12 navbar-inverse text-center'>";
page +=        "<div class='navbar-header' >";
page +=          "<a class='navbar-brand active' href='http://"+IPaddress+"'>Centrum dowodzenia</a>";
page +=       " </div> " ;
page +=    "</div>";
page +=  "</div>";
page +=    "<div class='okregi'>";
page +=      "<div class='col-xs-4' style='text-align: center;' ><span class='chart' data-percent=";
page += fireplaceTMP;
page +=     ">Kominek<span class='percent'></span></div>";
page +=      "<div class='col-xs-4' style='text-align: center;'><span class='chart ' data-percent=";
page += pumpFireplace;
page +=       ">Pompa<span class='percent'></span></div>";
page +=      "<div class='col-xs-4' style='text-align: center;'><span class='chart ' data-percent=";
page += hysteresis;
page +=     ">Histereza<span class='percent'></span></div>";
page +=    "</div>";
page +=    "<div class='row'>";
page +=     "<div class='col-xs-10 col-xs-offset-1 ' >";
page +=       "<form action='http://"+IPaddress+"' method='POST'>";
page +=        "<input type='number' name='pumpFireplace_input' placeholder='90' step='1' min='0' max='90'; class='form-control' style='width: 100%; font-size: 24px; text-align: center' id='usr'>";
page +=        "<button class='btn btn-default'  style='width: 100%; font-size: 24px;'  >Zapisz  Temp. Kominek</button>";
page +=      "</form>";
page +=    "</div>";
page +=     "<div class='col-xs-10 col-xs-offset-1 ' style=' padding-top:20px;'>";
page +=      "<form action='http://"+IPaddress+"' method='POST'>";
page +=        "<input type='number' name='hysteresis_input' placeholder='10' step='1' min='0' max='30' class='form-control' style='width: 100%; font-size: 24px; font-size: 24px; text-align: center' id='usr'>";
page +=        "<button class='btn btn-default' style='width: 100%; font-size: 24px;' >Zapisz histereze</button>";
page +=      "</form>";
page +=     "</div>";
page +=      " <div class='col-xs-10 col-xs-offset-1' style=' padding-top:20px;'>";
page +=     "<a href='http://"+IPaddress+"' class='btn btn-info btn-lg' style='width: 100%; '><span class='glyphicon glyphicon-refresh'></span> Refresh </a>";
page +=  "</body>";
page +=  "</html>";
   ;

    server.send(200, "text/html", page);
  });
  
  server.begin(); 

}

void loop(void) {
  int x = 10;
  int y = 20;
  nokiaLCD();
  Serial.write(x);
  Serial.write(y);


if (server.args() > 0 ) { // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Argument_Name = server.argName(i);
      if (server.argName(i) == "hysteresis_input") {
 
        int tmp= server.arg(i).toInt();
          if(tmp != 0){
          if(tmp != hysteresis){
             hysteresis =  tmp;
            digitalWrite(ledPin, HIGH);
            delay(100);
          }
        } 
        Clients_Response1 = server.arg(i);
           
      }
        if (server.argName(i) == "pumpFireplace_input") {
             pumpFireplace =  server.arg(i).toInt(); 
             Clients_Response2 = server.arg(i);
            digitalWrite(ledPin, HIGH);
            delay(100);
     }
    }   
  }
 digitalWrite(ledPin, LOW);

server.handleClient();
 //delay(100);  // Adjust this to change graph speed
}


/////////////////////////////////////

void nokiaLCD() {
//static const unsigned char ogien[] PROGMEM = 
//{
//0x0,0x0,0x0,
//0x0,0x40,0x0,
//0x0,0xC0,0x0,
//0x1,0x80,0x0,
//0x1,0x80,0x0,
//0x1,0x80,0x0,
//0x1,0xC4,0x0,
//0x1,0xC4,0x0,
//0x5,0xEC,0x0,
//0x7,0xFC,0x0,
//0x7,0xFE,0x0,
//0xF,0xDE,0x0,
//0xF,0xDF,0x0,
//0x1E,0x9F,0x0,
//0x1E,0xF,0x0,
//0x1E,0xF,0x0,
//0xE,0x6,0x0,
//0x6,0xC,0x0,
//0x1,0x0,0x0,
//0x0,0x0,0x0,
//
//};
  
  
  
  rssi = WiFi.RSSI();  // eg. -63

  display.clearDisplay();
   display.printf("TEMP.K= ");
  display.println(fireplaceTMP);
  display.printf("HIST=  " );
    display.println(hysteresis);

   display.printf("TEMP.P= " );
  display.println(pumpFireplace);
//display.setTextSize(2); 
 //display.print(fireplaceTMP);
// display.println("C'");
//display.drawBitmap(28, 24, ogien, 24, 20, 1);



  //draw an antenna
//  display.drawLine(55, 32, 55, 40, BLACK);
//  display.drawLine(56, 32, 56, 40, BLACK);
//  display.drawLine(52, 32, 55, 36, BLACK);
//  display.drawLine(51, 32, 55, 37, BLACK);
//  display.drawLine(59, 32, 56, 36, BLACK);
//  display.drawLine(60, 32, 56, 37, BLACK);

  int signal_level = 30;
  signal_level = map(WiFi.RSSI(), -70, 0, 4, 0);
    for (int x = 0; x < signal_level; x++)
    {
       display.drawLine(70 + 2 * x, 48, 70 + 2 * x, 48 - x, BLACK);
    }


  display.display();



}




void Connection() {
  WiFi.begin(myssid, mypass);
  display.print("Podlaczanie do sieci");
  display.display();

  // Wait for successful connection
  int i = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
    i++;
    if ( i > 20) {
      isConected = false;
      break;
    }
  }

  if (isConected == true) {


    display.clearDisplay();
    display.println("Polaczono do");
    display.println(myssid);
    display.display();
    delay(2000);
  }
  else {
    display.clearDisplay();
    display.println("NIE POLACZONO!");
    display.display();
    delay(2000);
  }

}




