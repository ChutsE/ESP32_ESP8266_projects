#include <WiFi.h>
#include "song.h"

#define array_length 80558 

void setup() {
 Serial.begin(115200);
 pinMode(26, OUTPUT); //DAC
}
void loop() {
  int a=micros();
  for(int i=0; i<=array_length;i++){
    dacWrite(26,rawData[i]);
    delayMicroseconds(100);
  }
  Serial.println(micros()-a);
delay(400);
}
