#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include "DHT.h"



#define DHTTYPE DHT11
#define DHTPIN 9
DHT dht(DHTPIN, DHTTYPE); 
int buzzer=5;
int ledred=4;
int ledgreen=3;
int ledlight=2;
int IR =A0;
int LDR=A1;
int echo=12;
int trig=13;
int gas=11;
int flame=10;
//int dht=9;
int fan= 6;
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
  Serial.begin(9600);
  pinMode(ledred,OUTPUT);
  pinMode(ledgreen,OUTPUT);
  pinMode(ledlight,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(LDR,INPUT);
  pinMode(gas,INPUT);
  pinMode(flame,INPUT);
 // pinMode(dht,INPUT);
  pinMode(fan,OUTPUT);
}
void loop() {
  //Balcony intrusion alarm *********************************************************************************************************************
delay(500);
Serial.println("");
Serial.println(analogRead(A0));

if(digitalRead(IR)==0)       //DISTANCE IS TO BE CHANGED
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
  if (cm<15 && light<50 )
    { digitalWrite(ledlight,HIGH);
      Serial.print("Entry light ON\n");
      Serial.println();
      }
    else{
      digitalWrite(ledlight,LOW);
       Serial.println("Entry light OFF\n");
       Serial.println();}
  //GAS FLAME ALARM *********************************************************************************************************************
  if( digitalRead(gas) == HIGH || digitalRead(flame) == HIGH){
    digitalWrite(ledred,HIGH);
    digitalWrite(ledgreen,LOW);
    tone(buzzer,1000);
    delay(1000);
    noTone(buzzer);
     delay(100); 
     if (digitalRead(gas) == HIGH ) {
      Serial.print("GAS leak detected\n");
       Serial.println();}
     if(digitalRead(flame)==HIGH) {
     Serial.print("FIRE detected\n");
       Serial.println();} 
     if(digitalRead(flame)==HIGH && digitalRead(gas) == HIGH) {
     Serial.print("FIRE detected\n");
       Serial.println();
       Serial.print("GAS leak detected\n");
       Serial.println();} 
      }
     
    /*digitalWrite(window,HIGH);
    delay(2000);
    digitalWrite(window,LOW);
    delay(10000);
    }*/
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
  float h = dht.readHumidity();
 float t = dht.readTemperature();
 Serial.println(h);
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
