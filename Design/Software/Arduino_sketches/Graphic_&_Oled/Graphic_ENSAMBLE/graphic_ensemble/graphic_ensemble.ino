//EDIT: AGGIUSTARE LA COMPATIBILITA' CON IL CODICE DELL'M1 (aggiustare per matchare parsePage ecc)
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <IRremote.h>

// If using software SPI (the default case):
//#define OLED_MOSI  MOSI //10
//#define OLED_CLK   SCK  //9
//#define OLED_DC    D7   //1
//#define OLED_CS    D8   //28
//#define OLED_RESET RST  //13
//Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define string_default "Default tag"
//#define RECV_PIN 4

//SU 2F0, Destra CD0, GIU AF0, SINISTRA 2D0

//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix ");
//#endif

//IRrecv irrecv(RECV_PIN);
//IRsend irsend;
//decode_results results;
bool h_rapp=1;
short PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
short Signal;                // holds the incoming raw data. Signal value can range from 0-1024
short Threshold = 550;            // Determine which Signal to "count as a beat", and which to ingore. 
short deanimate = 0, seconds = 0, mode = 0, curs = 0, old_curs = 0, maximum_r = 7, standard_r = 4, flag = 0, scrolly, minY, old_signal=0,page=0;

class CELL
{
  public:
    String tag;
    short x, y, radius;
    bool hovering;
    void activate();
    void deactivate();
    void set_values (short, short, short);
    void set_activity (String);
    void set_hovering (bool);
    void animate();
    void deanimate();
};

void CELL::animate()
{
  if (radius < maximum_r)
    radius++;
}

void CELL::activate()
{ display.fillCircle(x , y , radius, WHITE);
  display.setCursor( 64 - (tag.length() * 3), 28);
  Serial.println(tag);
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(1);
  display.println(tag);
  display.display();
}

void CELL::deactivate()
{
  display.fillCircle(x , y , maximum_r + 1, BLACK);

  if (radius > standard_r)
    radius = radius - 1;
  display.drawCircle(x , y , radius, WHITE);
  display.fillRect( 20, 28, 144, 8, BLACK);
  display.display();
}

void CELL::deanimate()
{
  display.fillCircle(x , y , maximum_r + 1, BLACK);
  if (radius > standard_r)
    radius = radius - 1;
  display.drawCircle(x , y , radius, WHITE);

}

void CELL::set_values (short set_x, short set_y, short set_radius)
{
  x = set_x;
  y = set_y;
  radius = set_radius;
}

void CELL::set_activity (String set_tag)
{
  tag = set_tag;
}

void CELL::set_hovering (bool set_hovering)
{
  hovering = set_hovering;
}

CELL matrix[6];


void initialize_matrix( String str1,String str2,String str3,String str4,String str5,String str6,int page)
{
  matrix[0].set_values (42, 12, standard_r);
  matrix[0].set_activity (str1);
  matrix[0].set_hovering (0);
  Serial.println("1.h");        //numbers are not wrong

  matrix[1].set_values (64, 8, standard_r);
  matrix[1].set_activity (str2);
  matrix[1].set_hovering (0);
  Serial.println("2.h");

  matrix[2].set_values (86, 12, standard_r);
  matrix[2].set_activity (str3);
  matrix[2].set_hovering (0);
  Serial.println("3.h");

  matrix[3].set_values (42, 48, standard_r);
  matrix[3].set_activity (str4);
  matrix[3].set_hovering (0);
  Serial.println("4.h");

  matrix[4].set_values (64, 52, standard_r);
  matrix[4].set_activity (str5);
  matrix[4].set_hovering (0);
  Serial.println("5.h");

  matrix[5].set_values (86, 48, standard_r);
  matrix[5].set_activity (str6);
  matrix[5].set_hovering (0);
  Serial.println("6.h");

  display.fillRect( 120, 54, 8, 10, BLACK);
  display.setCursor( 120, 54);
  //display.println(pageCount[mode]);
}


void initialize_matrix_line( String str1,String str2,String str3,String str4,String str5,String str6)
{
  matrix[0].set_values (26, 16, standard_r);
  matrix[0].set_activity (str1);
  matrix[0].set_hovering (0);
  Serial.println("1.h");        //numbers are not wrong

  matrix[1].set_values (44, 16, standard_r);
  matrix[1].set_activity (str2);
  matrix[1].set_hovering (0);
  Serial.println("2.h");

  matrix[2].set_values (62, 16, standard_r);
  matrix[2].set_activity (str3);
  matrix[2].set_hovering (0);
  Serial.println("3.h");

  matrix[3].set_values (80, 16, standard_r);
  matrix[3].set_activity (str4);
  matrix[3].set_hovering (0);
  Serial.println("4.h");

  matrix[4].set_values (98, 16, standard_r);
  matrix[4].set_activity (str5);
  matrix[4].set_hovering (0);
  Serial.println("5.h");

  matrix[5].set_values (116, 16, standard_r);
  matrix[5].set_activity (str6);
  matrix[5].set_hovering (0);
  Serial.println("6.h");

  display.fillRect( 120, 54, 8, 10, BLACK);
  display.setTextWrap(true);
}


void setup()   {
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  // Clear the buffer.
  display.clearDisplay();
  display.display();
  initialize_matrix_line(string_default,string_default,string_default,string_default,string_default,string_default);
  //initialize_matrix(string_default,string_default,string_default,string_default,string_default,string_default,page); //give default values (replecable)
  //  irrecv.enableIRIn(); // Start the receiver
}

void loop() {


  if (mode == 0)
  {
    if (flag == 0)      // if the screen base of object have never been initialized before/ we're coming from another modality
      /********************************************drawing the base of the CELL ensemble***********************/
    { int i;
      for (i = 0; i < 6; i++)
      { matrix[i].deactivate();
        flag = 1;
      }
    }
    /*********************************************************************************************************/

    Serial.println("cicle"); //beginning of cicles

    //   results.value=0;
    /*
      irrecv.decode(&results);
      irrecv.resume();
      Serial.println(results.value, DEC);

      if (results.value==3536)
      {
      mode++;
      results.value=0;
      }
      else if (results.value==3280)
      curs=curs+1;
      else if (results.value==720)
      curs=curs-1;
      else if (results.value==2800)
      curs=curs+3;
      else if (results.value==752)
      curs=curs-3;
    */

    /*****************************checking the legality of curs variable******************************************/
    if (curs == 6)
      curs = 0;
    else if (curs < 0)
      curs = 0;
    else if (curs > 6)
      curs = curs % 6;
    /*************************************************************************************************************/

    Serial.println(curs);
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


    /*******************************Reduction of the CELL objects*************************************************/
    short de;
    for (de = 0; de < 6; de++)
      if (de != curs)
        matrix[de].deanimate();
    /*************************************************************************************************************/


    //   results.value=0;


  }
  /*else if (mode == 1)
  { if (flag=0)
    {
    display.setTextSize(7);
    display.setTextColor(WHITE);
    display.setTextWrap(true);
    scrolly    = display.height();
    minY = - 60 * strlen(string_default);
    flag=1;
    }
    
    display.clearDisplay();
    display.setCursor(0, scrolly);
    display.print(string_default);
    display.display();

    if(--scrolly < minY) 
    scrolly = display.height();
    

    /*      irrecv.decode(&results);
          irrecv.resume();
          Serial.println(results.value, HEX);
          Serial.println("cicle");

            if (results.value==2672)
            {mode++;
             flag=0;
             results.value=0;
            }
    */
  //}*/
  else if (mode == 2)
  {
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value. 
  Serial.println(Signal);                                          // Assign this value to the "Signal" variable.
  
  if((Signal>300)&&(Signal<600))
  {
  if((Signal>old_signal+7)||(Signal<old_signal-7))
  {Serial.println("if");                    // Send the Signal value to Serial Plotter.
                                              // signal:950=x:64 whole screen
   Signal = ((Signal*32)/950)  ;            //zoomed if betwee(300) and (600)
   
   if (h_rapp==0)
   {
    display.fillCircle( (display.width()/2)-Signal/2 , (display.height()/2)-10, Signal,WHITE);
    display.fillCircle( (display.width()/2)+Signal/2 , (display.height()/2-10), Signal,WHITE);
    display.fillTriangle( (display.width()/2)-Signal*1.5,(display.height()/2)-10, (display.width()/2)+Signal*1.5 , (display.height()/2)-10, (display.width()/2) ,display.height()/2+Signal*1.5 , WHITE);
    display.fillCircle( (display.width()/2)-Signal/2 , (display.height()/2)-10, Signal-5,BLACK);
    display.fillCircle( (display.width()/2)+Signal/2 , (display.height()/2-10), Signal-5,BLACK);
    display.fillTriangle( ((display.width()/2)-Signal*1.5)-5,(display.height()/2)-10, ((display.width()/2)+Signal*1.5)-5 , (display.height()/2)-10, (display.width()/2) ,(display.height()/2+Signal*1.5)-5 , BLACK);
    display.display();
    display.clearDisplay();
   }
   else         
   {
    display.drawLine(scrolly-1, old_signal, scrolly, Signal, WHITE);
    display.display();

   scrolly++;
   
    if (scrolly>128)
    {  scrolly=0;
      display.clearDisplay(); 
    }
   
   }
   
   
   
    if(Signal > Threshold)
    {  
    }
    else {   }
      delay(10);
      }
    
    old_signal=Signal;
   }
  }
  else if (mode==3) //profile mode (inner profile)
    {
     //initialize matrix for profiles mode take strings from 
    initialize_matrix_line(string_default,string_default,string_default,string_default,string_default,string_default);
    
    }
}
