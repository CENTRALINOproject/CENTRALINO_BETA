/*
 * If an IR code is received, record it.
 * Copyright to Ken Shirriff, modifyed by Filippo Castellani.
   ATTACCA IL PIN DELL'IR AL 2 DIGITAL
 */

#include <IRremote.h>

int RECV_PIN = 2;
int incomingByte = 0;
bool Flag_Record=0;
bool Flag_Welcome=0;


IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

// Storage for the recorded code
int codeType = -1; // The type of code
unsigned long codeValue; // The code value if not raw
unsigned int rawCodes[RAWBUF]; // The durations if raw
int codeLen; // The length of the code
int toggle = 0; // The RC5/6 toggle state

// Stores the code for later playback

void storeCode(decode_results *results) {
  codeType = results->decode_type;
  int count = results->rawlen;
  if (codeType == UNKNOWN) {
    Serial.println("Received unknown code, saving as raw");
    codeLen = results->rawlen - 1;
    // To store raw codes:
    // Drop first value (gap)
    // Convert from ticks to microseconds
    // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      } 
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(rawCodes[i - 1], DEC);
      Serial.print("_");
    }
    Serial.println("");
  }
  else {
    if (codeType == NEC) {
      Serial.print("Received NEC: ");
      if (results->value == REPEAT) {
        // Don't record a NEC repeat value as that's useless.
        Serial.println("repeat; ignoring.");
        return;
      }
    } 
    else if (codeType == SONY) {
      Serial.print("Received SONY: ");
      codeLen = results->rawlen - 1;
    for (int i = 1; i <= codeLen; i++) {
      if (i % 2) {
        // Mark
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS;
        Serial.print(" m");
      } 
      else {
        // Space
        rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS;
        Serial.print(" s");
      }
      Serial.print(rawCodes[i - 1], DEC);
      Serial.print("_");
    }
    Serial.println("");
    } 
    else if (codeType == PANASONIC) {
      Serial.print("Received PANASONIC: ");
    }
    else if (codeType == JVC) {
      Serial.print("Received JVC: ");
    }
    else if (codeType == RC5) {
      Serial.print("Received RC5: ");
    } 
    else if (codeType == RC6) {
      Serial.print("Received RC6: ");
    } 
    else {
      Serial.print("Unexpected codeType ");
      Serial.print(codeType, DEC);
      Serial.println("");
    }
    Serial.println(results->value, HEX);
    codeValue = results->value;
    codeLen = results->bits;
  
  //inserire funzione per il salvataggio degli attributi dell'oggetto IR
  }
}

void record_IR ()
  {
//PARTE INIZIALE DA SOSTITUIRE CON TRIGGER FLEX SENSOR    
   Serial.print(" Benvenuto alla procedura guidata per la creazione di un record \n Vuoi iniziare la creazione ?\n");

      while(Flag_Welcome!=1) 
      { if (Serial.available()>0)
           incomingByte=Serial.read();
          if ((incomingByte==89)||(incomingByte==121))
          {
           Serial.println("Inizio...");
           Flag_Welcome=1;
          }
        else
         delay(400);
      }
      
   Serial.println(" Invia il segnale IR da registrare, direziona il telecomando verso il sensore con la X sopra");
      while (Flag_Record!=1) 
       {
        if (irrecv.decode(&results)!=false)
         {
          storeCode(&results);
          irrecv.resume(); // resume receiver ATTENZIONE--------------------------------------------------------Controllare se crea problemi
          Flag_Record=1;
          Serial.println("Ricevuto correttamente");
         }
        else
        delay(400);
       }
           Flag_Record=0;
           Flag_Welcome=0;

   show_IR(&results);
           //Function to store rawbuf, rawlen and frequency(=38) on the SD card
           //Store_IR();
return;
  }

/* void Store_IR()
 * {results 
 * 
 * } 
 */

void show_IR(decode_results *results)
{ codeType = results->decode_type;
  Serial.println(results->value, HEX);
  codeValue = results->value;
  codeLen = results->bits;
    if (codeType == UNKNOWN) { 
      Serial.println("UNKNOWN");
      Serial.println(codeValue);
      Serial.println(codeLen);}
    else if (codeType == NEC) {
      Serial.println("NEC");
      Serial.println(codeValue);
      Serial.println(codeLen);}
    else if (codeType == SONY) {
      Serial.println("SONY");
      Serial.println(codeValue);
      Serial.println(codeLen);} 
    else if (codeType == PANASONIC) {
      Serial.println("PANASONIC");
      Serial.println(codeValue);
      Serial.println(codeLen);}
    else if (codeType == JVC) {
      Serial.println("JVC");
      Serial.println(codeValue);
      Serial.println(codeLen);}
    else if (codeType == RC5) {
      Serial.println("RC5");
      Serial.println(codeValue);
      Serial.println(codeLen);} 
    else if (codeType == RC6) {
      Serial.println("RC6");
      Serial.println(codeValue);
      Serial.println(codeLen);} 
    else {
      Serial.print("Unexpected codeType ");
      Serial.print(codeType, DEC);
      Serial.println(codeValue);
      Serial.println(codeLen);
      Serial.println("");
    }
    //Serial.println(results->value, HEX);
  }  
  
  
  
void loop() 
  {
   record_IR();
  }

  
