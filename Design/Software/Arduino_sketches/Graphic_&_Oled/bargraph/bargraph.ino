/*

  The purpose of this program is to test and demonstrate the display performance of the 128 x 64 display

  Code will be used to display a bar graph from measured input voltage or random number
  The display is a Balance world Inc 0.96" Inch Yellow and Blue I2c IIC Serial 128x64 Oled LCD Oled LED Module for
  Arduino Display 51 Msp420 Stim32 SCR


  This could tested with a Mega but should work with an UNO

  Kasprzak (c) 2015

  Pin connections
  Arduino   device
  A0    Voltage read (5K pot across +5, and ground)
  A1
  A2
  A3
  A4    SDA (if no SDA pin)
  A5    SCL (if not SCL pin)
  1
  2
  3
  4
  5
  6
  7
  8
  9
  10
  11
  12
  13
  SDA   SDA
  SLC   SLC

  Graphics Libraries
  https://github.com/adafruit/Adafruit-GFX-Library
  https://github.com/adafruit/Adafruit_SSD1306

  display
  http://www.amazon.com/Balance-world-Yellow-Arduino-Display/dp/B00ZI01RO0/ref=sr_1_1?ie=UTF8&qid=1448860339&sr=8-1&keywords=balance+world+.96


*/

#include <SPI.h>
#include <Wire.h>

#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 Display(OLED_RESET);

int r = 0;
int i = 0;

void setup()   {


  Display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)

  // i'll follow the license agreement and display the Adafruit logo
  // and since they were nice enough to supply the libraries
  Display.clearDisplay();
  Display.display();
  delay (1000);

  DrawTitles();

}


void loop() {

  // get some dummy data to display
  // now that the display is build, display it...
  Display.display();

}


void DrawTitles(void) {

  Display.setTextSize(2);
  Display.setTextColor(WHITE);
  Display.setCursor(0, 0);
  Display.println("First Test");

  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor(0, 19);
  //Display.println("Measured Volts");
  Display.println("CIAO");
  //Display.display();

}


