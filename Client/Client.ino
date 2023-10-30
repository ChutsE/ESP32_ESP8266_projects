 #include <ESP8266WiFi.h>

const char* ssid = "INFINITUMt77r";
const char* password = "FES38613921";

const char* host = "192.168.1.66"; //host a conectar

void setup()
{

  Serial.begin(115200);
  Serial.println();
 
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");
}


void loop()
{
  WiFiClient client;  //Now we should declare a client that will be contacting the host (server)

  Serial.printf("\n[Connecting to %s ... ", host);

  if (client.connect(host, 80))  //In next line we will connect to the host and check the connection result. Note 80, that is the standard port number used for web access.
  {
    //Estamos conectados al host
    Serial.println("connected]");
    
    Serial.println("[Sending a request]");
    //we send request the host to provide specific information we need. This is done using the HTTP GET request 
    client.print(String("GET /")+"\r\n"+
                 "HTTP/1.1 \r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );


    Serial.println("[Response:]");
    
    while (client.connected() || client.available())
    { 
        String line = client.readStringUntil(':');
        Serial.println(value);
        
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(200);
}
