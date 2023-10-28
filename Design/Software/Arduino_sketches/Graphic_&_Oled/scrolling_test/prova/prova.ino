#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_DC     9
#define OLED_CS     8
#define OLED_CLK   12
#define OLED_MOSI  11
#define OLED_RESET 10
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

char message[] = "ABCDEFGHILMNOPQRSTUVZ";
int  x, minX;

void setup() {
  //Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextSize(7);
  display.setTextColor(WHITE);
  display.setTextWrap(true);
  x    = display.height();
  minX = - 60 * strlen(message); // 12 = 6 pixels/character * text size 2
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, x);
  display.print(message);
  display.display();
  Serial.println(x); 
  
  if(--x < minX) 
  x = display.height();

}
