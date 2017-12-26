
bool heating(){
  if(fireplaceTMP >= pumpFireplace){
    heatingFlag = true;
     digitalWrite(ledPin, HIGH);
     return true;
   //  serial.print(1);
  }

int pumpOFF = pumpFireplace - hysteresis;
    if(pumpOFF <= fireplaceTMP){
    heatingFlag = false;
//    serial.print(1);
  return false;

  }
}

