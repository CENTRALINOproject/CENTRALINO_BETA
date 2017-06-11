#include <MemoryFree.h>
#include <SoftwareSerial.h>
#include <IRremote.h>
#include <string.h>
#define rxPin 9
#define txPin 10
#define RECV_PIN 4
#define default_relay 6  //Pin of relay 1 (rel[1])
#define total_relay 1    // Total number of relay connected

#include <Wire.h>
#include "RTClib.h"
#include <TimeAlarms.h>
#include <TimeLib.h>
#include <Time.h>


/********RTC*********************/
RTC_DS1307 rtc;
tmElements_t tm;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif


/********BLUETOOTH***************/
SoftwareSerial bluetooth(rxPin, txPin);

/*******Infra-Red****************/
IRrecv irrecv(RECV_PIN);
decode_results results;

String bluetooth_Buffer;

struct function 
{
  int activity;
  int extra_value;
  int extra_value2;
} function_temp;

struct relay
{
  int socket = 0;
  int hour_daily_end = 61;
  int minute_daily_end = 61;
  int second_daily_end_and_start = 0;
  int hour_daily_start = 61;
  int minute_daily_start = 61;

  int timer_off_hour = 61;
  int timer_off_minute = 61;
  int timer_off_second = 61;

  int timer_on_hour = 61;
  int timer_on_minute = 61;
  int timer_on_second = 61;

  int description = 0;
  
} rel[1];

void all_rel_HIGH()
{
  for (int i=0; i<total_relay ;i++)
  {
   digitalWrite(rel[i].socket, HIGH);
   
   Serial.print("Impostato ad HIGH pin n. ");
   Serial.print(rel[i].socket);
   Serial.print(" per struttura rel[] n. ");
   Serial.println(i);
  }
}

void init_output_rel()
{
  for (int i=0; i<total_relay ;i++)
   {
   pinMode(rel[i].socket, OUTPUT);
   
   Serial.print("Inizializzato pin n. ");
   Serial.print(rel[i].socket);
   Serial.print(" per struttura rel[] n. ");
   Serial.println(i);
   }
}

void setup ()
 {
  #ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
  #endif	 
	 
  Serial.begin(9600); //set baud rate
  bluetooth.begin(9600);
  
  init_output_rel(); //Declare output all relays
  all_rel_HIGH();    //Set HIGH all relays
  delay(1000);

  irrecv.enableIRIn(); // Start the receiver
  
  //FOR DEBUG 
  /* Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  */

  if (! rtc.begin()) {
  Serial.println("Couldn't find RTC");
  while (1);
  }
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   // rtc.adjust(DateTime(year, month, day, hour, min, sec)); IF NEED ADJUSTMENTS
  }
  
  DateTime now = rtc.now();
  setTime(now.hour(),now.minute(),now.second(),now.month(),now.day(),now.year());

  /*********PLEASE HERE DECLARE THE PIN'S OF THE RELAYS, ONE EACH REL[] STRUCTURE*******/
  //example : rel[].socket = pin connected to relay ;
  rel[0].socket = default_relay;

 }
 
void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void digitalClockDisplay()
{
  // digital clock display of the time
  DateTime now = rtc.now();
  Serial.print(now.hour());
  printDigits(now.minute());
  printDigits(now.second());
  Serial.println(); 
}

bool ir_handler(decode_results *results)
{
  if (results->value == 0xA90 )
    turn_off();
    else 
      return false;
}

void bluetooth_handler()
{
  char check = ' ';
  check = bluetooth.read();
  if ((int(check)!= 13)&&(int(check)!= 10 )&&(int(check)!= 32)) //Ignore '\r' , '\n' and spaces
  bluetooth_Buffer += check;
  else
  {
  Serial.println("Relivated unprintable chars, ASCII value is : ");
  Serial.println(int(check));
  }
  
  Serial.print("Value of bluetooth buffer is = '");
  Serial.print(bluetooth_Buffer);
  Serial.println("'");
  
  if (check==']')
  bluetooth_Parser();
  
}

/********************************MEANINGS OF DESCRIPTIONS*********************************
1 = Lamp
2 = Chandelier
3 = Computer
4 = Fridge
5 = Fan
6 = Microwave
7 = Charger
*****************************************************************************************/

/**********************STRUCTURE BLUETOOTH PACKAGE****************************************
 * ('figures' in italian : 'cifre')
 * ([) Message opening                                                    1 position : [0]
 * (1st number, two figures) Activity                                     2 position : [2]
 * (,)                                                                    1 position : [3]
 * (2nd number , four figures) Extra_value                                4 position : [7]
 * (,)																	                                  1 position : [8]
 * (3rd number , six figures) Extra_value2                                6 position : [14]
 * (]) message closer                                                     1 position : [15] Total = 16
 *****************************************************************************************/



void bluetooth_Parser()
{ Serial.println("Open bluetooth parser");
  if (int(bluetooth_Buffer.length())!=16) //Hard coded dimensions and particularities of the message
  {Serial.println("Lenght check not passed");
   Serial.println(int(bluetooth_Buffer.length()));
   bluetooth_Buffer = "";}  
    else if (bluetooth_Buffer[0]!='[')
     {Serial.println("Opener check not passed");
     Serial.println(bluetooth_Buffer[0]);
     bluetooth_Buffer = "";}
      else if (bluetooth_Buffer[3]!=',')
      {Serial.println("First comma check not passed");
      Serial.println(bluetooth_Buffer[3]);
      bluetooth_Buffer = "";}
		   else if (bluetooth_Buffer[8]!=',')
	     {Serial.println("Second comma check not passed");
       Serial.println(bluetooth_Buffer[8]);
       bluetooth_Buffer = "";}
		     else if (bluetooth_Buffer[15]!=']')
         {Serial.println("Closer check not passed");
          Serial.println(bluetooth_Buffer[15]);
           bluetooth_Buffer = "";}
		      else
          {  String temp_string;
             long temp=0;

              Serial.print("Received package : ");
              Serial.println(bluetooth_Buffer);
              temp_string=bluetooth_Buffer.substring(1,3); // substring (from [index] ,to [index we want in the sub +1]) https://www.arduino.cc/en/Reference/StringSubstring
              temp=atoi(temp_string.c_str());
              function_temp.activity = int(temp);
              
              temp_string=bluetooth_Buffer.substring(4,8); 
              temp=atoi(temp_string.c_str());
              function_temp.extra_value = int(temp);
              
			        temp_string=bluetooth_Buffer.substring(9,15);
              temp=atoi(temp_string.c_str());
              function_temp.extra_value2 = int(temp);

            bluetooth_Buffer=""; //Reset buffer for new packets

            activity_manager();
        }
  
}


// ACTIVITY MANAGER
void activity_manager ()
{ Serial.println("Open activity manager");
  Serial.println(function_temp.activity);
  digitalClockDisplay();
  
  if (function_temp.activity == 1) // Turn OFF relay n. extra_value
      turn_off();
  
  if (function_temp.activity == 2 ) // Turn On relay n. extra_value
      turn_on();

  if (function_temp.activity == 3 ) // Set timer to turn ON relay n. extra_value in time extra_value2
	    set_timer_on();

  if (function_temp.activity == 4 ) // Set timer to turn OFF relay n. extra_value in time extra_value2
      set_timer_off();
    
  if (function_temp.activity == 5 ) // Set daily START on relay n. extra_value in time extra_value2
      set_daily_start();

  if (function_temp.activity == 6 ) // Set daily END on relay n. extra_value in time extra_value2
      set_daily_end();

  if (function_temp.activity == 50 ) // REQUEST of OFFER 
      bluetooth_offer();

                     // 51 is an OFFER package (Will never be received on CLIENTino)
                   
                
                     // 99 is a CLOSE communication_packet (Will never be received on CLIENTino)*/

	return;
}

void bluetooth_offer()
{
  Serial.println("Offer now :");
  for (int i=0; i<total_relay; i++)
    send_package(51, rel[i].socket, rel[i].description );
  
  send_package(99, 0, 0); //Close comunication
return;
}

void send_package(int activity, int extra_value, int extra_value2)
{ Serial.println("FLAG send package"); 
  
  Serial.println("Send package");
  
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());
  
  if ((activity>99)||(extra_value>9999)||(extra_value2>999999))
  { 
    Serial.println("Unable to send the packet because of uncorrect values");
  }
  else
  {
    String packet = "";
    String aux_activity = zero_padd(activity, 2);
    Serial.println("THIS IS AUX ACT");
    Serial.println(aux_activity);
    
    String aux_extra_value = zero_padd(extra_value, 4);
    Serial.println("THIS IS AUX EXTRA");
    Serial.println(aux_extra_value);
    
    String aux_extra_value2 = zero_padd(extra_value2, 6);
    Serial.println("THIS IS AUX EXTRA 2");
    Serial.println(aux_extra_value2);

    packet += '[';
    packet += aux_activity; 
    packet += ',';
    packet += aux_extra_value;
    packet += ',';
    packet += aux_extra_value2;
    packet += ']';

    Serial.print("This is packet");
    Serial.println(packet);             //packet.concat(aux_activity)   
  }
  
return;
}

String zero_padd(int value, int spaces)
{ Serial.println("FLAG zero_padd");
  String result="";
  Serial.println("FLAG zero_padd1");
  int padds=spaces, aux_value=value;
  Serial.println("FLAG zero_padd2");

  if(aux_value!=0)
  {
    do 
    {
    Serial.println("FLAG zero_padd3");
    Serial.println(aux_value);
    if (aux_value > 0)
      {
      aux_value = aux_value / 10;
      Serial.println("This is aux after /10");
      Serial.println(aux_value);
      padds--;
      }
  }
  while (aux_value > 0);

  }
  else
  {
  padds=spaces-1;  
  }
  
  Serial.print("This is value :");
  Serial.println(value);
  Serial.print("This is spaces :");
  Serial.println(spaces);
  Serial.print("This is padds :");
  Serial.println(padds);
  
  if (padds!=0)
  {
    if (padds==1)
    result="0";
  else if (padds==2)
    result="00";
  else if (padds==3)
    result="000";
  else if (padds==4)
    result="0000";
  else if (padds==5)
    result="00000";
  else if (padds==6)
    result="00000";
  }

  result.concat(value);

  return result;
}

void set_timer_off()
{
  rel[function_temp.extra_value].timer_off_hour = hour()+function_temp.extra_value2/3600;
  rel[function_temp.extra_value].timer_off_minute = minute()+function_temp.extra_value2/60;
  rel[function_temp.extra_value].timer_off_second = second()+function_temp.extra_value2%60;
  adjust_timer_off(); 
}

void set_timer_on()
{

  rel[function_temp.extra_value].timer_on_hour = hour();//+function_temp.extra_value2;///3600;
  rel[function_temp.extra_value].timer_on_minute = minute();//+function_temp.extra_value2;///60;
  rel[function_temp.extra_value].timer_on_second = second()+function_temp.extra_value2 ;//%60;
  adjust_timer_on();
              
}

void adjust_timer_on()
{ 
  if(rel[function_temp.extra_value].timer_on_second >= 60)
  {  
   rel[function_temp.extra_value].timer_on_minute  = rel[function_temp.extra_value].timer_on_minute + rel[function_temp.extra_value].timer_on_second / 60;
   rel[function_temp.extra_value].timer_on_second = rel[function_temp.extra_value].timer_on_second % 60;
  }

  if(rel[function_temp.extra_value].timer_on_minute >= 60)
  { rel[function_temp.extra_value].timer_on_hour = rel[function_temp.extra_value].timer_on_hour + rel[function_temp.extra_value].timer_on_minute / 60 ;
    rel[function_temp.extra_value].timer_on_minute = rel[function_temp.extra_value].timer_on_minute % 60;
  }

  if(rel[function_temp.extra_value].timer_on_hour >= 24)
  rel[function_temp.extra_value].timer_on_hour = rel[function_temp.extra_value].timer_on_hour % 24;

}


void adjust_timer_off()
{ 
    if(rel[function_temp.extra_value].timer_off_second >= 60)
  {  
   rel[function_temp.extra_value].timer_off_minute  = rel[function_temp.extra_value].timer_off_minute + rel[function_temp.extra_value].timer_off_second / 60;
   rel[function_temp.extra_value].timer_off_second = rel[function_temp.extra_value].timer_off_second % 60;
  }

  if(rel[function_temp.extra_value].timer_off_minute >= 60)
  { rel[function_temp.extra_value].timer_off_hour = rel[function_temp.extra_value].timer_off_hour + rel[function_temp.extra_value].timer_off_minute / 60 ;
    rel[function_temp.extra_value].timer_off_minute = rel[function_temp.extra_value].timer_off_minute % 60;
  }

  if(rel[function_temp.extra_value].timer_off_hour >= 24)
  rel[function_temp.extra_value].timer_off_hour = rel[function_temp.extra_value].timer_off_hour % 24;
  
  }

void set_daily_end()
{
  rel[function_temp.extra_value].hour_daily_end = function_temp.extra_value2/100;
  rel[function_temp.extra_value].minute_daily_end = function_temp.extra_value2%100;
}

void set_daily_start()
{
  rel[function_temp.extra_value].hour_daily_start = function_temp.extra_value2/100;
  rel[function_temp.extra_value].minute_daily_start = function_temp.extra_value2%100;
}

int match_time(int i)
{ int result=0; //No match founded

  int hour_now = hour();
  int minute_now = minute();
  int second_now = second();
   
   if ( (rel[i].hour_daily_end==hour_now) && (rel[i].minute_daily_end==minute_now) ) //return 6 (same n. as activity)
    if ( rel[i].second_daily_end_and_start==second_now)
    {

      Serial.println(" match with daily_end, I'll return 6");

      result=6;
      }
 
   if ( (rel[i].hour_daily_start==hour_now) && (rel[i].minute_daily_start==minute_now)) //return 5 (same n. as activity)
      if( rel[i].second_daily_end_and_start==second_now )
      {
      Serial.println(" match with daily_start, I'll return 5");
      result=5; //Turn on founded
      }
   
   if ( (rel[i].timer_off_hour==hour_now) && (rel[i].timer_off_minute==minute_now ) ) //return 4 (same n. as activity)
        if (rel[i].timer_off_second==second_now)
        {
        Serial.println(" match with timer_off, I'll return 4");
        rel[i].timer_off_hour = 61;
        rel[i].timer_off_minute = 61;
        rel[i].timer_off_second = 61;
        result=4;
        }
    if ( (rel[i].timer_on_hour==hour_now ) && (rel[i].timer_on_minute==minute_now) ) //return 3 (same n. as activity)
        if( rel[i].timer_on_second==second_now )
        {
        Serial.println(" match with timer_on, I'll return 3");
           
        rel[i].timer_on_hour = 61;
        rel[i].timer_on_minute = 61;
        rel[i].timer_on_second = 61;
        result=3;
       }

   return result;
}

void turn_by_match()
{ Serial.println("Checking by match : ");
  for (int i=0; i<total_relay; i++)
   {int match_result = match_time(i);
    if (match_result == 6) //daily_end
    turn_off_pin(i);
     else if (match_result == 5) //daily_start
     turn_on_pin(i);
      else if (match_result == 3) //timer_on
      turn_on_pin(i);
       else if (match_result == 4) //timer_off
       turn_off_pin(i);
        else Serial.println("No match founded");
   }
}


void turn_on_pin(int index)
{
      digitalWrite( index , LOW);
      Serial.println("ON");
      delay (4000);       
}

void turn_off_pin(int index)
{
      digitalWrite( index , HIGH);
      Serial.println("OFF");
      delay (4000);       
}

void turn_off()
{
      digitalWrite(function_temp.extra_value , HIGH);
      Serial.println("OFF");
      delay (4000);                                     //this is to not overcharge the relay
  }

void timer_turn_off()
{
      digitalWrite( rel[function_temp.extra_value2].socket , HIGH);
      Serial.println("OFF");
      delay (4000);                                     //this is to not overcharge the relay
  }

void timer_turn_on()
{
      digitalWrite( rel[function_temp.extra_value2].socket , LOW);
      Serial.println("ON");
      delay (4000);                                     //this is to not overcharge the relay
  }

void turn_on()
{
      digitalWrite(function_temp.extra_value , LOW);
      Serial.println("ON");
      delay (4000);                                      //this is to not overcharge the relay
  }


void digitalClockDisplay_notRTC()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void loop ()
 {  
  if(bluetooth.available())
    bluetooth_handler();  
  
  if (irrecv.decode(&results))
    ir_handler(&results);

  digitalClockDisplay_notRTC();
  turn_by_match();
  
  Serial.print("freeMemory()=");
  Serial.println(freeMemory());

  //delay(500);
  }
