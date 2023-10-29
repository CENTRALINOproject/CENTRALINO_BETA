#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremote.h>

// If using software SPI (the default case):
#define OLED_MOSI  11
#define OLED_CLK   12
#define OLED_DC    9
#define OLED_CS    8
#define OLED_RESET 10
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define string_default "Default tag"
#define RECV_PIN 4

//SU 2F0, Destra CD0, GIU AF0, SINISTRA 2D0

//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix ");
//#endif

IRrecv irrecv(RECV_PIN);
IRsend irsend;
decode_results results;


  int seconds=0, mode=0, curs=0, old_curs=0;

  class CELL
        {     
    public:
        String tag;
        String command;
        int x,y,width,height;
        bool hovering;
        void activate();
        void deactivate();
        void set_values (int,int,int,int);
        void set_activity (String,String);
        void set_hovering (bool); 
        };



  void CELL::activate()
    { 
      display.fillRect(x-2 ,y-2 ,width+4, height+4, WHITE);
      display.setCursor(2, 25);
      display.setTextColor(WHITE, BLACK);
      display.setTextSize(1);
      display.println(tag);
      display.display();
    }

  void CELL::deactivate()
    {
      display.fillRect(x -2 ,y-2 , width+4, height+4, BLACK);
      display.drawRect(x ,y , width, height, WHITE);
      display.fillRect(0, 25 ,128, 7, BLACK);
      display.display();
    }

  void CELL::set_values (int set_x, int set_y,int set_width,int set_height) 
    {
      x = set_x;
      y = set_y;
      width = set_width;
      height = set_height;
    }

  void CELL::set_activity (String set_tag, String set_command)
    {
      tag=set_tag;
      command=set_command;
    }
  
  void CELL::set_hovering (bool set_hovering)
    {
      hovering=set_hovering;
    }

  CELL matrix[6];

  void initialize_matrix()
    { 
      matrix[0].set_values (2,2,38,8);
      matrix[0].set_activity (string_default,string_default);
      matrix[0].set_hovering (0);
      Serial.println("1.h");        //numbers are not wrong
    
      matrix[1].set_values (43,2,38,8);
      matrix[1].set_activity (string_default,string_default);
      matrix[1].set_hovering (0);
      Serial.println("2.h");
    
      matrix[2].set_values (86,2,38,8);
      matrix[2].set_activity (string_default,string_default);
      matrix[2].set_hovering (0);
      Serial.println("3.h");
    
      matrix[3].set_values (2,14,38,8);
      matrix[3].set_activity (string_default,string_default);
      matrix[3].set_hovering (0);
      Serial.println("4.h");
    
      matrix[4].set_values (43,14,38,8);
      matrix[4].set_activity (string_default,string_default);
      matrix[4].set_hovering (0);
      Serial.println("5.h");
    
      matrix[5].set_values (86,14,38,8);
      matrix[5].set_activity (string_default,string_default);
      matrix[5].set_hovering (0);
      Serial.println("6.h"); 
    }



void setup()   {                
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  // Clear the buffer.
  display.clearDisplay();
  initialize_matrix();
  irrecv.enableIRIn(); // Start the receiver
}

int flag=0;

void loop() {


  if (mode==0)
  { 
    if (flag==0)
     { int i;
        for (i=0;i<6;i++)
        {matrix[i].deactivate();
        delay(200);
        flag=1;
      }
     }

   results.value=0;
   irrecv.decode(&results);
   irrecv.resume();
   delay(300);
   Serial.println(results.value, DEC);
   Serial.println("cicle");
   
   if (results.value==3536)
   {mode++;
    results.value=0;}
   else if (results.value==3280)
   curs=curs+1;
   else if (results.value==720)
   curs=curs-1;
   else if (results.value==2800)
   curs=curs+3;
   else if (results.value==752)
   curs=curs-3;
   
   if (curs==6)
   curs=0;
   else if (curs<0)
   curs=0;
   else if (curs>6)
   curs=curs%6;

   Serial.println(curs);
   
   
   matrix[curs].activate();
   
   if(curs!=old_curs)
    {
      matrix[curs].activate();
      matrix[old_curs].deactivate();
    }
   
   old_curs=curs;

   results.value=0;
  
   
  }
    else if (mode==1)
    { display.clearDisplay();
      clck_base();
      clck_line();
      testo();
      display.display();
      display.clearDisplay();
      
      irrecv.decode(&results);
      irrecv.resume();
      delay(100);
      Serial.println(results.value, HEX);
      Serial.println("cicle");
        
        if (results.value==2672)
        {mode++;
         flag=0;
         results.value=0;
        }
   }
    else if (mode==2)
    {
      mode=0;
    }
  }

void testo()
{display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(2,2);
  display.println("TIME \n IS \n NOW :");



  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(100,12);
  display.println(seconds);
  delay(1);
  }

void clck_line()
{ 
  
  int arrivex,arrivey,thirty;
  thirty=32;

  if (seconds==0)
   {arrivex= 32+thirty;
    arrivey= 6; }
  else if (seconds==5)
   {arrivex= 37+thirty;
    arrivey= 8; }
  else if (seconds==10)
   {arrivex= 40+thirty;
    arrivey= 11; }
  else if (seconds==15)
   {arrivex= 41+thirty;
    arrivey= 16; }
  else if (seconds==20)
   {arrivex= 40+thirty;
    arrivey= 21; }
  else if (seconds==25)
   {arrivex= 37+thirty;
    arrivey= 24; }
  else if (seconds==30)
   {arrivex= 32+thirty;
    arrivey= 26; }
  else if (seconds==35)
   {arrivex= 26+thirty;
    arrivey= 24; }
  else if (seconds==40)
   {arrivex= 23+thirty;
    arrivey= 21; }
  else if (seconds==45)
   {arrivex= 22+thirty;
    arrivey= 16; }
  else if (seconds==50)
   {arrivex= 26+thirty;
    arrivey= 11; }
  else if (seconds==55)
   {arrivex= 26+thirty;
    arrivey= 8; }
  else if (seconds==60)
   {arrivex= 32+thirty;
    arrivey= 6; }
  

  
  display.drawLine(display.width()/2, display.height()/2, arrivex, arrivey, WHITE);
  
  if (seconds==60)
    {seconds=0;}
  else
    seconds=seconds+5;
  
}


void clck_base()
{
  display.drawCircle(display.width()/2, display.height()/2, 15, WHITE);
  }


 
