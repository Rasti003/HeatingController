



int PompaJeden = 7;
int PompaDwa =  6;
int PompaTrzy = 5;
int PompaCztery =4;
int PompaPiec =2;
 int PompaSzesc =3;


int kominekPIN =53; // pin kominka
int kominekStan =0;
int piecPIN =52;
int piecStan =0;


void setup() {

Serial.begin(9600);



  
 
pinMode(PompaJeden,OUTPUT);
pinMode(PompaDwa,OUTPUT);
pinMode(PompaTrzy,OUTPUT);
pinMode(PompaCztery,OUTPUT);
pinMode(PompaPiec,OUTPUT);
pinMode(PompaSzesc, OUTPUT);




digitalWrite(PompaJeden,HIGH);
  digitalWrite(PompaDwa,HIGH);
digitalWrite(PompaTrzy,HIGH);
digitalWrite(PompaCztery,HIGH);
digitalWrite(PompaPiec,HIGH);
digitalWrite(PompaSzesc,HIGH);

pinMode (kominekPIN ,INPUT_PULLUP);
pinMode (piecPIN ,INPUT_PULLUP);
}

void loop() {


  kominekStan = digitalRead(kominekPIN);    // 
piecStan = digitalRead(piecPIN);    // 


  
 // Serial.println(kominekStan);
 // Serial.println(analogRead(piecPIN));
  KominekDziala();
  PiecDziala();
  resetPompy();


}


void KominekDziala(){
if(kominekStan == LOW)
{


digitalWrite(PompaJeden,LOW);
digitalWrite(PompaDwa,LOW);
digitalWrite(PompaTrzy,LOW);
digitalWrite(PompaCztery,LOW);
digitalWrite(PompaPiec,LOW);
}
else
{
    digitalWrite(PompaJeden,HIGH);
}

}



void PiecDziala(){

if(piecStan == LOW)
{
  digitalWrite(PompaDwa,LOW);
  digitalWrite(PompaTrzy,LOW);
  digitalWrite(PompaCztery,LOW);
  digitalWrite(PompaPiec,LOW);
  digitalWrite(PompaSzesc,LOW);
}
  else
  {
  digitalWrite(PompaSzesc,HIGH);
  }
  }


void resetPompy(){
  if(piecStan ==HIGH && kominekStan == HIGH)
  {
    digitalWrite(PompaDwa,HIGH);
  digitalWrite(PompaTrzy,HIGH);
  digitalWrite(PompaCztery,HIGH);
  digitalWrite(PompaPiec,HIGH);
  digitalWrite(PompaSzesc,HIGH);
  }
}





