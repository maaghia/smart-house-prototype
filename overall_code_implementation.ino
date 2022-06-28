#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


#define DHTTYPE DHT11
#define DHTPIN 4
DHT dht(DHTPIN, DHTTYPE); 
int buzzer=6;
int ledred=8;
int ledgreen=7;
int ledlight=13;
int IR =5;
int LDR=A1;
int echo=12;
int trig=11;
int gas=10;
int flame=A2;
int fan= 9;
//ULTRASONIC function declataration
 long microsecondsToCentimeters(long microseconds) // method to covert microsec to centimeters
{
   return microseconds / 29 / 2;
}
void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Welcome to MySmartHouse\n");
  pinMode(IR,INPUT);
  pinMode(ledred,OUTPUT);
  pinMode(ledgreen,OUTPUT);
  pinMode(ledlight,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(LDR,INPUT);
  pinMode(gas,INPUT);
  pinMode(flame,INPUT);
  dht.begin();
  pinMode(fan,OUTPUT);
}
void loop() {
  float h = dht.readHumidity();
 float t = dht.readTemperature();
  //Balcony intrusion alarm *********************************************************************************************************************

 int statusSensor = digitalRead (IR);
if(statusSensor==1)       //DISTANCE IS TO BE CHANGED
{
  digitalWrite(ledred,HIGH);
  digitalWrite(ledgreen,LOW);
  Serial.print("INTRUSION detected\n");
    tone(buzzer,1000); //alarm on
    delay(1000);
    noTone(buzzer);
     delay(100); 
  }
 else{
    digitalWrite(ledred,LOW);
    digitalWrite(ledgreen,HIGH);
   Serial.print("NO intrusion detected\n");
   Serial.println();
    noTone(buzzer); //alarm off
    } 
    //ENTRY_LIGHT_SYSTEM *********************************************************************************************************************
    int light=analogRead(LDR);
    long duration ,cm;
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trig, LOW);
  
  duration = pulseIn(echo, HIGH); // using pulsin function to determine total time
  cm = microsecondsToCentimeters(duration); // calling method
  if (cm<30 && light<500 )
    { digitalWrite(ledlight,HIGH);
      Serial.print("Entry light ON\n");
      Serial.println();
      }
    else{
      digitalWrite(ledlight,LOW);
       Serial.print("Entry light OFF\n");
       Serial.println();}
  //GAS FLAME ALARM *********************************************************************************************************************
  if( digitalRead(gas) == HIGH || digitalRead(flame) == LOW){
    digitalWrite(ledred,HIGH);
    digitalWrite(ledgreen,LOW);
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
     delay(100); 
     if (digitalRead(gas) == HIGH ) {
      Serial.print("GAS leak detected\n");
       Serial.println();}
     if(digitalRead(flame)==LOW) {
     Serial.print("FIRE detected!\n");
       Serial.println();} 
     if(digitalRead(flame)==LOW && digitalRead(gas) == HIGH) {
     Serial.print("FIRE detected!\n");
       Serial.println();
       Serial.print("GAS leak detected!\n");
       Serial.println();} 
      }
    else{
    digitalWrite(ledred,LOW);
    digitalWrite(ledgreen,HIGH);
    noTone(buzzer);
    }
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  Serial.print("light intensity:\t");
  Serial.println(light);
  Serial.println();
  
  delay(100);
  //Temperature & Humidity with fan *********************************************************************************************************************
  
 Serial.print("hum:\t");
 Serial.println(h);
 Serial.print("temp:\t");
 Serial.println(t);
  if(h>=60 || t>=25)
  { 
    digitalWrite(fan,HIGH);
  }
  else
  {
    digitalWrite(fan,LOW);
  }
  delay(500);
  
  
}
