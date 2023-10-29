#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#define MIRF_PAYLOAD 32

byte rxData[MIRF_PAYLOAD+1];
byte txData[MIRF_PAYLOAD+1];
const char msg[]= "Ciao";
int msgIndex = 0;

void setup(){
  memset(rxData, 0, sizeof(rxData));
  memset(txData, 0, sizeof(txData));
  Serial.begin(9600);
  Mirf.cePin = 9;
  Mirf.csnPin = 10;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte*)"clie1");
  Mirf.payload = MIRF_PAYLOAD;   
  Mirf.channel = 10;
  Mirf.config();
}

void loop() {
  Mirf.setTADDR((byte*)"serv1");
  memcpy(txData, msg + msgIndex, MIRF_PAYLOAD);
  Mirf.send(txData);
  while(Mirf.isSending()){
  }
  delay(10);
  unsigned long time = millis();
  while(!Mirf.dataReady()){
    if (( millis() - time ) > 1000) {
      Serial.println("timeout");
      return;
    }
  }
  Mirf.getData(rxData);
  Serial.println((const char*)rxData);
  msgIndex += MIRF_PAYLOAD;
  if (msgIndex + MIRF_PAYLOAD > sizeof(msg)) {
    msgIndex = 0;
  }
}
