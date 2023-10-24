#include <SPI.h>
#include <SD.h>0
#include <IRremote.h>

//samsung on off 4250 -4150 550 -1500 550 -1500 550 -1500 550 -500 500 -500 550 -500 500 -500 550 -450 600 -1500 550 -1500 500 -1500 550 -500 550 -450 550 -500 550 -500 500 -500 550 -450 550 -1500 550 -500 550 -450 550 -500 550 -500 500 -500 500 -500 550 -1500 550 -500 550 -1500 500 -1550 500 -1500 550 -1500 600 -1500 500 -1500 550 

File myFile;
String file_name = "testa.txt"; //NAME MUST BE UPDATED ANY TIME NOT TO INCUR IN DOUBLE WRITING ON THE SAME FILE
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) { ; /*wait for serial port to connect. Needed for native USB port only*/ }
  irrecv.enableIRIn();
  Serial.print("Initializing SD card...");
  if (!SD.begin(4))
    {Serial.println("initialization failed!");
    return;
    }
  Serial.println("initialization done."); 
}

void loop() {
if (irrecv.decode(&results)) {//Serial.println(results.value, HEX);//dump(&results); // Use it to display the IR code on the serial monitore
    write_Ir(&results);
    irrecv.resume(); // Receive the next value
    }
}

void write_Ir(decode_results *results)
{
  myFile = SD.open(file_name, FILE_WRITE);
  if (myFile) 
  {
  Serial.print(file_name);
  Serial.print(" :");
/*************************************USING_SAME_SAVING_WAY_THEN_WHEN_SHOWING_THE_RAW*******************************************************/   
      int count = results->rawlen;
      int caa;
      for (int i = 1; i < count; i++) 
      {
        if (i & 1) 
          {
          myFile.print(results->rawbuf[i]*USECPERTICK - MARK_EXCESS);
          myFile.print(',');
          /*caa = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
          Serial.print("mark is : ");
          Serial.println(caa);*/
          }
        else 
          {
          //HO TOLTO UNSIGNED LONG A RESULTS -> RAWBUFF
          myFile.print(results->rawbuf[i]*USECPERTICK + MARK_EXCESS);
          myFile.print(',');
          /*caa = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
          Serial.print("space is : ");
          Serial.println(caa);*/
          }
      }
/*****************************************************************************************************************************/    
    myFile.print(']');
    myFile.close();
    Serial.println("done.");
  }
  else {Serial.println("error opening the file");}
}

/*
void dump(decode_results *results) 
{
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {Serial.print("Unknown encoding: ");}
  else if (results->decode_type == NEC) {Serial.print("Decoded NEC: ");}
  else if (results->decode_type == SONY) {Serial.print("Decoded SONY: ");}
  else if (results->decode_type == RC5) {Serial.print("Decoded RC5: ");}
  else if (results->decode_type == RC6) {Serial.print("Decoded RC6: ");}
  else if (results->decode_type == PANASONIC) 
  { Serial.print("Decoded PANASONIC - Address: ");
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
  }
  else if (results->decode_type == LG) {Serial.print("Decoded LG: ");}
  else if (results->decode_type == JVC) {Serial.print("Decoded JVC: ");}
  else if (results->decode_type == AIWA_RC_T501) {Serial.print("Decoded AIWA RC T501: ");}
  else if (results->decode_type == WHYNTER) {Serial.print("Decoded Whynter: ");}
  Serial.print(results->value, HEX);
  Serial.print(" (");
  Serial.print(results->bits, DEC);
  Serial.println(" bits)");
  Serial.print("Raw (");
  Serial.print(count, DEC);
  Serial.print("): ");

  for (int i = 1; i < count; i++) 
  {  
    if (i & 1) 
      {
      Serial.write('-');
      Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
      }
    else 
      {
      Serial.write('-');
      Serial.print((unsigned long) results->rawbuf[i]*USECPERTICK, DEC);
      }
    Serial.print(" ");
  }
  Serial.println();
}
*/
