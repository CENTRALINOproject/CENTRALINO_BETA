#include <SPI.h>
#include <SD.h>0
#include <IRremote.h>

File myFile;
String file_name = "testp.txt"; //NAME MUST BE UPDATED ANY TIME NOT TO INCUR IN DOUBLE WRITING ON THE SAME FILE
IRsend irsend;
char signal_to_send[80]; 

void setup() {
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

  int c=0;
  for(c=0;c<80;c++)
  { 
    signal_to_send[c]=0;
  }
  
  read_Raw(&signal_to_send[80]);
  send_Raw_Ir(&signal_to_send[80]);
  
}

void read_Raw(char signal_to_send[]){
 int supp;
 char eye[1];
 int i = 0;
 myFile = SD.open(file_name);
  if (myFile) { 
  Serial.println(file_name);
  while (myFile.available()) 
  {
      myFile.read(eye[1],1);
      switch (eye[1]) {
            case ',':
                i++;
                supp=0;
                break;
            case ']':
                myFile.close();
                break;
            default:
                supp*10;
                supp+(eye[1],DEC);
                supp-48;
                signal_to_send[i]+supp;
                break;
      }

    }
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  int c=0;
  for(c=0;c<80;c++)
  { Serial.print(signal_to_send[c],DEC);
    Serial.print('_');
  }
  
 Serial.println("finito read");
}

void send_Raw_Ir(char signal_to_send[])
  {
  Serial.println("iniziato send");
  int khz = 38;
  int signal_s[80];
  
  int i=0;
  for(i=0;i<80;i++)
  { signal_s[i]=(signal_to_send[i],DEC);
    Serial.print(signal_s[i]);
    Serial.print('+');
  }
  
  irsend.sendRaw(signal_s,80, khz); //Note the approach used to automatically calculate the size of the array.
  Serial.println("finito_send");
  }

