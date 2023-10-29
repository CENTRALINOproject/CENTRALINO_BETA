#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <IRremote.h>

// If using software SPI (the default case):
#define OLED_MOSI  11
#define OLED_CLK   12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10
#define string_default
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
 
int rxPin = 2;
int txPin = 3;
SoftwareSerial bluetooth(rxPin, txPin);
 
String message,old_message; //string that stores the incoming message
short counter=0;
char check;
const int Led = 13;
 
void setup()
{
  Serial.begin(9600); //set baud rate
  bluetooth.begin(9600); //set baud rate
  pinMode(Led,OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.display();
}
 
void loop()
{ 
  while(bluetooth.available())
  {
      check=int(bluetooth.read());
     if (check!=62)
        {
        check=char(check);
        message+=check;
        display.clearDisplay();
        }
      else
      {
        Serial.print(message);
        display.setCursor( 0, 0);
        //Serial.print(64 - message.length() * 6);
        display.setTextColor(WHITE, BLACK);
        display.setTextSize(2);
        display.setTextWrap(true);
        display.println(message);
        
         if(old_message==message)
        counter++;
        else
        counter=0;
       
        display.setCursor( 64, 30);
        display.setTextSize(2);
        display.print(counter);  
        display.display();
        old_message=message;
        message="";
      }
  }


}


