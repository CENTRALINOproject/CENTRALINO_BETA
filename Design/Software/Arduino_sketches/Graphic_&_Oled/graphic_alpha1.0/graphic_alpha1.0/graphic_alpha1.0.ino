
//necessary libraries
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>     //Might be necessary to look to the library and check which of the resolution is uncommented
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

void setup() {

	// If using software SPI (the default case):
	//#define OLED_MOSI  MOSI //10
	//#define OLED_CLK   SCK  //9
	//#define OLED_DC    D7   //1
	//#define OLED_CS    D8   //28
	//#define OLED_RESET RST  //13
	//Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


	//if using software I2C (our screen case-aliexpress screen)
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
	// Clear the buffer.
	display.clearDisplay();
	display.display();

}

void loop() {
 
 graphic();

 }

void graphic ()
{	switch ( mode ) 
	{
		case 0 /*circular*/:
		graphic_Kernel();
		break;
		case 1 /*profiles*/:
		graphic_Kernel();
		break;
		case 2 /*notification*/:
		notification_Kernel();
		break;
		default:
		// Code
		break;
	}
	old_mode = mode;
	display.display(); //print what have been processed in the whole function
}

void notification_Kernel()
{
	
}

void graphic_Kernel ()
{	
	if (old_mode != mode)      // if the screen base of object have never been initialized before/ we're coming from another modality
      /******************************drawing the base of the CELL ensemble***********************************/
    { for (int i = 0; i < 6; i++)
      matrix[i].deactivate(); }
    /*********************************************************************************************************/
	
	if (curs != old_curs)
    {
      matrix[curs].activate();
      matrix[old_curs].deactivate();
    }
    else
    {
      matrix[curs].animate();
      matrix[curs].activate();
    }
    old_curs = curs;
}

void cell_reduction(short curs)
{
    /*******************************Reduction of the CELL objects*************************************************/
    for (short de = 0; de < 6; de++)
      if (de != curs) // reduce (radius-1) all the cells except the one that we're on (a.k.a. curs)
        matrix[de].deanimate();
    /*************************************************************************************************************/
}

int position_check(short curs) //return curs if possible otherwise return another applicable position
{
	/*****************************checking the legality of curs variable******************************************/
    if (curs == 6)
      curs = 0;
    else if (curs < 0)
      curs = 0;
    else if (curs > 6)
      curs = curs % 6;
    /*************************************************************************************************************/
return curs;
}

void initialize_matrix_line( String str1,String str2,String str3,String str4,String str5,String str6) //profiles mode
{
  matrix[0].set_values (26, 16, standard_r);
  matrix[0].set_activity (str1);
  matrix[0].set_hovering (0);
  Serial.println("1");        

  matrix[1].set_values (44, 16, standard_r);
  matrix[1].set_activity (str2);
  matrix[1].set_hovering (0);
  Serial.println("2");

  matrix[2].set_values (62, 16, standard_r);
  matrix[2].set_activity (str3);
  matrix[2].set_hovering (0);
  Serial.println("3");

  matrix[3].set_values (80, 16, standard_r);
  matrix[3].set_activity (str4);
  matrix[3].set_hovering (0);
  Serial.println("4");

  matrix[4].set_values (98, 16, standard_r);
  matrix[4].set_activity (str5);
  matrix[4].set_hovering (0);
  Serial.println("5");

  matrix[5].set_values (116, 16, standard_r);
  matrix[5].set_activity (str6);
  matrix[5].set_hovering (0);
  Serial.println("6");

  display.fillRect( 120, 54, 8, 10, BLACK);
  display.setTextWrap(true);
}

void initialize_matrix( String str1,String str2,String str3,String str4,String str5,String str6,short page) //circular mode
{
  matrix[0].set_values (42, 12, standard_r);
  matrix[0].set_activity (str1);
  matrix[0].set_hovering (0);
  Serial.println("1");        //numbers are not wrong

  matrix[1].set_values (64, 8, standard_r);
  matrix[1].set_activity (str2);
  matrix[1].set_hovering (0);
  Serial.println("2");

  matrix[2].set_values (86, 12, standard_r);
  matrix[2].set_activity (str3);
  matrix[2].set_hovering (0);
  Serial.println("3");

  matrix[3].set_values (42, 48, standard_r);
  matrix[3].set_activity (str4);
  matrix[3].set_hovering (0);
  Serial.println("4");

  matrix[4].set_values (64, 52, standard_r);
  matrix[4].set_activity (str5);
  matrix[4].set_hovering (0);
  Serial.println("5");

  matrix[5].set_values (86, 48, standard_r);
  matrix[5].set_activity (str6);
  matrix[5].set_hovering (0);
  Serial.println("6");


}

class CELL
{
  public:
    String tag;
    short x, y, radius,page;
    bool hovering;
    void activate();
    void deactivate();
    void set_values (short, short, short);
    void set_activity (String);
    void set_hovering (bool);
    void animate();
    void deanimate();
};

void CELL::animate()//increment radius of cell
{
  if (radius < maximum_r)
    radius++;
}

void CELL::activate()//display the cell's tag and make it white
{ 
  display.fillCircle(x , y , radius, WHITE);
  display.setCursor( 64 - (tag.length() * 3), 28);
  Serial.println(tag);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.println(tag);
  display_page();
}

void CELL::deactivate()//erase the cell's tag and make it black
{
  display.fillCircle(x , y , maximum_r + 1, BLACK);

  if (radius > standard_r)
    radius = radius - 1;
  display.drawCircle(x , y , radius, WHITE);
  display.fillRect( 20, 28, 144, 8, BLACK);
  display_page();
}

void CELL::deanimate()//decrement radius of cell
{
  display.fillCircle(x , y , maximum_r + 1, BLACK);
  if (radius > standard_r)
    radius = radius - 1;
  display.drawCircle(x , y , radius, WHITE);

}

void CELL::set_values (short set_x, short set_y, short set_radius, short set_page)
{
  x = set_x;
  y = set_y;
  radius = set_radius;
  page = set_page;
}

void CELL::set_activity (String set_tag)
{
  tag = set_tag;
}

void CELL::set_hovering (bool set_hovering)
{
  hovering = set_hovering;
}

void display_page()
{ 
	display.fillRect( 120, 54, 8, 10, BLACK);
	display.setCursor( 120, 54);
	display.println(page);
}
