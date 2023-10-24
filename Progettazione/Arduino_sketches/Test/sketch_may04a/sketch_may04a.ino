#include <SoftwareSerial.h>
#define rxPin 9
#define txPin 8
/********BLUETOOTH***************/
SoftwareSerial bluetooth(rxPin, txPin);
void setup ()
 {
  
  Serial.begin(9600); //set baud rate
  bluetooth.begin(9600);
  delay(1000);
  
 }


void loop() {

  if(Serial.read())

}
