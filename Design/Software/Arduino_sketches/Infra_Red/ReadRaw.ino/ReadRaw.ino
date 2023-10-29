#include <SPI.h>
#include <SD.h>0
#include <IRremote.h>

File f;
String file_name = "testp.txt"; //NAME MUST BE UPDATED ANY TIME NOT TO INCUR IN DOUBLE WRITING ON THE SAME FILE
IRsend irsend;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
}

void loop() {
read_Raw(file_name);
}

void read_Raw(String path) {
   short int signalLenght = 0;
  //conta virgole e terminatore e metti in signalLenght, poi torna a posizione 0
  signalLenght = comma_counter(path);
        Serial.print("--");
        Serial.println(signalLenght);
  f.seek(0);
  
  if (SD.exists(path.c_str()))
    f = SD.open(path.c_str());
  else
    return;
 
  unsigned int signal_to_send[signalLenght];
  short int signalIndex = 0;
  String bufferText = "";
  char tmpChar;
  while (f.available()) {
    tmpChar = f.read();
    if (tmpChar == ',') 
      {
      signal_to_send[signalIndex] = atoi(bufferText.c_str()); //trasforma in intero
      Serial.print("current sigtosend :");
      Serial.println(signal_to_send[signalIndex]);
      bufferText = "";
        signalIndex++;
      }
    else if (tmpChar == '§') 
      {
      signal_to_send[signalIndex] = bufferText.toInt(); //trasforma in intero
      Serial.print("current sigtosend :");
      Serial.println(signal_to_send[signalIndex]);
      bufferText = "";
      break;
      }
    else 
      {
      bufferText = bufferText + tmpChar;
            Serial.println(tmpChar);
      }
  }
  f.close();
  int khz = 38;
  irsend.sendRaw(signal_to_send, sizeof(signal_to_send) / sizeof(signal_to_send[0]), khz); //Note the approach used to automatically calculate the size of the array.
  Serial.println("finito_send");
  delay(2000);
  return;
}

int comma_counter(String path)
{  if (SD.exists(path.c_str()))
    f = SD.open(path.c_str());
  else
    return;
  char tmpChar;
  short comma_numb=0;
  while (f.available()) 
   {
    tmpChar = f.read();
    if ((tmpChar == ',')||(tmpChar == '§')) 
    comma_numb++;
    }
  f.close();
return comma_numb;
}
