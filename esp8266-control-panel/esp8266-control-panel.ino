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
#include <OneWire.h>
#include <DallasTemperature.h>

// pins lcd
const int8_t RST_PIN = D2;
const int8_t CE_PIN = D1;
const int8_t DC_PIN = D6;
const int8_t BL_PIN = D0;

// pins
static  const  uint8_t ledPin = D3;
#define ONE_WIRE_BUS 2 //  DS18B20
//  wifi
const char* myssid = "Maciek";
const char* mypass = "Murzyn12";
//const char* myssid = "Janusz_COMPANY";
//const char* mypass = "Kleszczu!@";

// flag
bool isConected = true;
bool heatingFlag ;
//Server
ESP8266WebServer server(80);
String Argument_Name, Clients_Response1, Clients_Response2;
String page = "";

//value
int fireplaceTMP = 20;
int pumpFireplace = 80;
int hysteresis = 10;

//Signal strength
long rssi = 0;

Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);




void setup(void) {

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);


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

  server.begin();
  sensors.begin();
  sensors.setWaitForConversion(false); // ustawiamy aby sensor pobierał dane w tle
  sensors.requestTemperatures(); // żądanie odczytu
  digitalWrite(ledPin, LOW);
  
  Connection();
  websiteBigin();
  Serial.begin(9600);
}

void loop(void) {
  heating();
  nokiaLCD();
  websiteInput();
  digitalWrite(ledPin, LOW);
  server.handleClient();
 
}









