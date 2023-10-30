#include <WiFi.h>
#include <WiFiUdp.h>

WiFiUDP udp;

const char* ssid = "TP-FES";
const char* password = "FES38613921";

int mensaje;

IPAddress ip_local(192,168,0,247);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
IPAddress dns(8,8,8,8);
IPAddress dns_alt(1,1,1,1);

void setup()
{
  
  Serial.begin(115200);
  WiFi.config(ip_local, gateway, subnet, dns, dns_alt);
  

  pinMode(26, OUTPUT); //DAC
  
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
  udp.begin(5050);

}


void loop() 
{

 int packetSize = udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
      mensaje=udp.read();
   dacWrite(26,mensaje);
}

}

  
