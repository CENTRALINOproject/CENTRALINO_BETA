#include <SoftwareSerial.h>
#define relay 6
#define rxPin 9
#define txPin 8
SoftwareSerial bluetooth(rxPin, txPin);


void setup ()
 {
  Serial.begin(9600); //set baud rate
  bluetooth.begin(9600);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  delay(1000);
  
 }

void loop ()
 {char check = ' ';
  while(bluetooth.available())
   {
      check=bluetooth.read();
      //bluetooth_activate(check);
      Serial.println(check);
   }
 }

void bluetooth_activate (char ch)
{
   if (ch=='Y')
      {
        digitalWrite(relay , HIGH);
        bluetooth_Flush();
        Serial.println("ON");
        delay (4000);                                      //this is to not overcharge the relay
      }
      else if (ch=='N')
      {
        digitalWrite(relay , LOW);
        bluetooth_Flush();
        Serial.println("OFF");
         delay (4000);                                      //this is to not overcharge the relay
      }
     
  }

void bluetooth_Flush(){
  while(bluetooth.available() > 0) 
  {
    char t = bluetooth.read();
  }
}   
