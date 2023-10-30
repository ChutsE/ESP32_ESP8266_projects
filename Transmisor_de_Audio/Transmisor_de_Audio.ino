#include <WiFi.h>
#include "song.h"
#include <WiFiUdp.h>

int i;

WiFiUDP udp;

//Vars to acess WiFi
const char* ssid = "TP-FES";
const char* password = "FES38613921";

const char* host = "192.168.0.247"; //IP recepter

//Config to declare a static IP
IPAddress ip_local(192,168,0,139);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
IPAddress dns(8,8,8,8);
IPAddress dns_alt(1,1,1,1);

#define array_length 80558 
char code[]="0";

void setup() {
 Serial.begin(115200);
 WiFi.config(ip_local, gateway, subnet, dns, dns_alt);
 
 Serial.println();
 Serial.printf("Connecting to %s ", ssid);
 WiFi.begin(ssid, password);
  
 while (WiFi.status() != WL_CONNECTED)
 {
    delay(500);
    Serial.print(".");
 }
 Serial.println(" connected");

  
  Serial.printf("Your IP local is %s \n", WiFi.localIP().toString().c_str());

  
}


void loop() {
  int a=micros();
  
  
  for(i=0; i<=array_length;i++){
    sendUDP();
  }
  
  Serial.println(micros()-a);
  delay(400);
}

void sendUDP(){
    udp.beginPacket(host, 5050); 
    udp.write(rawData[i]);
    udp.endPacket();
}

void HEXtoSTRING(){
  for(int j=0;j<=array_length;j++){
     strncat(code,&rawData,j);
  }
}
