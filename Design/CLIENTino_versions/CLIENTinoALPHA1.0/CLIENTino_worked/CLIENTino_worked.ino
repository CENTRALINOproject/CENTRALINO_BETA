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
  int socket = default_relay;
  int hour_daily_end = 0;
  int minute_daily_end = 0;
  int hour_daily_start = 0;
  int minute_daily_start = 0;
  
} rel[1];

/*********PLEASE HERE DECLARE THE PIN'S OF THE RELAYS, ONE EACH REL[] STRUCTURE*******/
//example : rel[].socket = pin connected to relay ;

void all_rel_HIGH()
{
  for (int i=0; i<total_relay ;i++)
  digitalWrite(rel[i].socket, HIGH);
}

void init_output_rel()
{
  for (int i=0; i<total_relay ;i++)
   pinMode(rel[i].socket, OUTPUT); 
}

void setup ()
 {
  #ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
  #endif	 
	 
  Serial.begin(9600); //set baud rate
  bluetooth.begin(9600);
  
  init_output_rel();
  all_rel_HIGH();
  delay(1000);

  irrecv.enableIRIn(); // Start the receiver
  
  //FOR DEBUG 
  /* Serial.begin(57600);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  */
  
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
   // rtc.adjust(DateTime(year, month, day, hour, min, sec)); IF NEED ADJUSTMENTS
  }
  
  DateTime now = rtc.now();
  setTime((now.hour(),DEC),(now.minute(),DEC),(now.second(),DEC),(now.month(),DEC),(now.day(),DEC),(now.year(),DEC));

  //Declaring relay pin socket
  rel[1].socket = default_relay;
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
  bluetooth_Buffer += check;
  if (check==']')
  bluetooth_Parser();
  
}

/**********************STRUCTURE BLUETOOTH PACKAGE****************************************
 * ('figures' in italian : 'cifre')
 * ([) Message opening                                                    1 position : [0]
 * (1st number, two figures) Activity                                     2 position : [2]
 * (,)                                                                    1 position : [3]
 * (2nd number , four figures) Extra_value                                4 position : [7]
 * (,)																	                                  1 position : [8]
 * (3rd number , four figures) Extra_value2                               4 position : [12]
 * (]) message closer                                                     1 position : [13]
 *****************************************************************************************/



void bluetooth_Parser()
{
  if (int(bluetooth_Buffer.length())!=13) //Hard coded dimensions and particularities of the message
  bluetooth_Buffer = "";
    else if (bluetooth_Buffer[0]!='[')
    bluetooth_Buffer = "";
      else if (bluetooth_Buffer[3]!=',')
      bluetooth_Buffer = "";
		   else if (bluetooth_Buffer[8]!=',')
		    bluetooth_Buffer = "";
		     else if (bluetooth_Buffer[13]!=']')
         bluetooth_Buffer = "";
		      else
          {  String temp_string, temp_string_debug;
             long temp=0;
             //Processing the activity figures 
              temp_string=bluetooth_Buffer.substring(1,3); // substring (from [index] ,to [index we want in the sub +1]) https://www.arduino.cc/en/Reference/StringSubstring
              temp=atoi(temp_string.c_str());
              function_temp.activity = int(temp);
             //Processing the extra_value figures
              temp_string=bluetooth_Buffer.substring(4,8); 
              temp=atoi(temp_string.c_str());
              function_temp.extra_value = int(temp);
			       //Processing the extra_value2 figures
			        temp_string=bluetooth_Buffer.substring(9,13);
              temp=atoi(temp_string.c_str());
              function_temp.extra_value2 = int(temp);

            activity_manager();
        }
  
}


// ACTIVITY MANAGER
void activity_manager ()
{
  if (function_temp.activity == 1) // Turn OFF relay n. extra_value
      turn_off();
  
  if (function_temp.activity == 2 ) // Turn On relay n. extra_value
      turn_on();

  if (function_temp.activity == 3 ) // Set timer 
	    set_timer();
    
  if (function_temp.activity == 4 ) // Set daily start
      set_daily_start();

  if (function_temp.activity == 5 ) // Set daily end
      set_daily_end();

	return;
}

void set_timer()
{
	Alarm.timerOnce(function_temp.extra_value, turn_off);
}

void set_daily_end()
{
	Alarm.alarmRepeat(function_temp.extra_value2/100 ,function_temp.extra_value2%100, 0, turn_by_match);
  rel[function_temp.extra_value].hour_daily_end = function_temp.extra_value2/100;
  rel[function_temp.extra_value].minute_daily_end = function_temp.extra_value2%100;
}

void set_daily_start()
{
	Alarm.alarmRepeat(function_temp.extra_value2/100 ,function_temp.extra_value2%100, 0, turn_by_match);
  rel[function_temp.extra_value].hour_daily_start = function_temp.extra_value2/100;
  rel[function_temp.extra_value].minute_daily_start = function_temp.extra_value2%100;
}

int match_time(relay rel, int i)
{ int result=0; //No match founded
  DateTime now = rtc.now();
   if ((rel.hour_daily_end == (now.hour(),DEC)) && (rel.minute_daily_end == (now.minute(),DEC)))
   return result=1; //Turn off founded
     else if ((rel.hour_daily_start == (now.hour(),DEC) )&& (rel.minute_daily_start == (now.minute(),DEC)))
     return result=2; //Turn on founded
       else 
       return result=0;
}

void turn_by_match()
{
  for (int i=0; i<total_relay; i++)
   {if (match_time(rel[i],i) == 1)
    turn_off_pin(i);
     else if (match_time(rel[i],i) == 2)
     turn_on_pin(i);
       //else //No match founded
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

void turn_on()
{
      digitalWrite(function_temp.extra_value , LOW);
      Serial.println("ON");
      delay (4000);                                      //this is to not overcharge the relay
  }


void loop ()
 {
  if(bluetooth.available())
    bluetooth_handler();  
  
  if (irrecv.decode(&results))
    ir_handler(&results);
  //event_handler(&results);
 }
