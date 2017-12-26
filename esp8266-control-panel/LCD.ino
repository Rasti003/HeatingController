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

 char temp[400];
  sensors.requestTemperatures();
  float tempF = (sensors.getTempCByIndex(0));
  
  fireplaceTMP=tempF;
 
 
  display.clearDisplay();
  display.printf("TEMP.K= ");
  display.println(tempF);
  
  display.printf("HIST=  " );
  display.println(hysteresis);

   display.printf("TEMP.ZAL.P= " );
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

