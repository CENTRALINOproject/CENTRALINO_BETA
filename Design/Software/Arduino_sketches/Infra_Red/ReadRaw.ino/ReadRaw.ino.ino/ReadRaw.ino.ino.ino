#include <SPI.h>
#include <SD.h>0
#include <IRremote.h>

//THE DEFAULT PIN FOR TRANSMITTING IS DIGITAL 3 ON ARDUINO UNO
File f;
String file_name = "testr.txt"; //NAME MUST BE UPDATED ANY TIME NOT TO INCUR IN DOUBLE WRITING ON THE SAME FILE
IRsend irsend;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {; /* wait for serial port to connect. Needed for native USB port only */ }
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
        /*Serial.print("--");
          Serial.println(signalLenght);*/
  f.seek(0);
  
  if (SD.exists(path.c_str()))
    f = SD.open(path.c_str());
  else
    return;
 
  unsigned long int signal_to_send[signalLenght];
  int converted[signalLenght];
  short int signalIndex = 0;
  String bufferText = "";
  char tmpChar;
  while (f.available()) 
  {
    tmpChar = f.read();
    if (tmpChar == ',') 
      {
      signal_to_send[signalIndex] = bufferText.toInt(); //trasforma in intero
      /*Serial.print("current sigtosend :");
        Serial.print(signal_to_send[signalIndex]);
        Serial.print("   casted int :");
        Serial.println((int)signal_to_send[signalIndex]); */
      bufferText = "";
        signalIndex++;
      }
    else if (tmpChar == ']') 
      {
      signal_to_send[signalIndex] = bufferText.toInt(); //trasforma in intero
      /*Serial.print("current sigtosend :");
        Serial.println(signal_to_send[signalIndex]);*/
      bufferText = "";
      break; //<- questo break l'ha messo Daniele, è necessario ? Probabilmente si se per sbaglio il file si crea con qualche errore
      }
    else 
      {
      bufferText = bufferText + tmpChar;
            Serial.println(tmpChar);
      }
  }
  f.close();
  int khz = 38;

/******************************************CONVERSION IN TO THE OTHER VECTOR*************************/
  for(int conv=0;conv < signalLenght;conv++)
  converted[conv] = (int)signal_to_send[conv];
/****************************************************************************************************/
  for(int l=0;l<100;l++)
  {
    irsend.sendRaw(converted, signalLenght, khz); 
    delay(200);
  }
  Serial.println("finito_send");
  delay(200);
  return;
}

int comma_counter(String path)
{  if (SD.exists(path.c_str()))
    f = SD.open(path.c_str());
  else
    return 0;
  char tmpChar;
  short comma_numb=0;
  while (f.available()) 
   {
    tmpChar = f.read();
    if ((tmpChar == ',')||(tmpChar == ']')) 
    comma_numb++;
    }
  f.close();
return comma_numb;
}
