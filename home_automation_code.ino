//fan 
int dir1=4;
int dir2=3;
int speedpin=5;
int mspeed;
int tpin=A3;
int tiltpin=2;
int tiltvalue;
int tvalue;

//bulbpin
int photorespin=A2;
int bulbpin=9;
int wait=250;
int pvalue;
int bvalue;

//servo & hr
#include <Servo.h>
int spin=12;
int pingpin=7;
int echopin=6;
float duration;
float distance;
Servo myservo;

void setup()
{
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);
  pinMode(speedpin, OUTPUT);
  pinMode(tpin, INPUT);
  pinMode(tiltpin, INPUT);
  digitalWrite(tiltpin, HIGH);
  
  //bulb pins
  pinMode (photorespin, INPUT);
  pinMode (bulbpin, OUTPUT);
  Serial.begin(9600);
  
  //servo & hr
  myservo.attach (spin);
  pinMode(pingpin, OUTPUT);
  pinMode(echopin, INPUT);
}

void loop()
{
  digitalWrite(dir1, LOW);			//setting motor direction
  digitalWrite(dir2, HIGH);
  tvalue=analogRead(tpin);			//reading temp sensor value 
 // Serial.println(tvalue);
  mspeed = (tvalue* 11.59) - (1831.36) ;	//temperature range is 27 to 37
  tiltvalue=digitalRead(tiltpin);		//reading tilt sensor value 
  if(tiltvalue == 1) {					//for good condition tilt value is 1 1 1
   if(mspeed >255) {
     mspeed = 255;
   }
   if(mspeed < 0) {
     mspeed = 0 ;
   }
  analogWrite(speedpin, mspeed);
  }
  else {
    digitalWrite(speedpin, LOW);
  }
  
  //for bulb
   pvalue=analogRead(photorespin);
  Serial.print(pvalue);
  if(pvalue>200 ){
    digitalWrite(bulbpin , HIGH);
    Serial.println("highest intensity");
  }
 // else if(pvalue>140 ){
 //   analogWrite(bulbpin , 100);
 //   Serial.println("medium intensity");
 // }
  else{
    digitalWrite(bulbpin, LOW);
    Serial.println("zero intensity");
  }
   
  //servo
  digitalWrite(pingpin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingpin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingpin, LOW);
  duration=pulseIn(echopin, HIGH);
 // Serial.print(duration);
  distance=0.0172*duration ;
  //Serial.println(distance);
  if(distance < 50) {		//if distance is less than 50 cm 
    myservo.write(90);
  }
  else{
    myservo.write(0);
  }
  
  delay(wait);
  
}