#include <ESP8266WiFi.h>

const char* ssid = "INFINITUMt77r";
const char* password = "f27cd6253e";

WiFiServer server(80);


#define led 4

void setup()
{
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}





void loop()
{
  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
     
        String line = client.readStringUntil('\r');
        Serial.print(line);
        client.println(prepareHtmlPage());
       
        
        if(line.indexOf("/onled")!=-1)digitalWrite(led,HIGH);
        
        break;
      
    }
    
    delay(200); // give the web browser time to receive the data

    // close the connection:
    client.stop();
    Serial.println("[Client disonnected]");
   
  }
}

String prepareHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            


           " <!DOCTYPE html>"+
"<html lang='es'>"+
"<head>"+
  "<meta charset='utf-8'>"+
  "<meta name='viewport' content='width=device-width, initial-scale=1.0'>"+
    "<meta http-equiv='refresh'"+
    "content='5'> "+ 
    
   " <title>"+
   "Visualizacion de datos"+
   "</title>"+
"</head>"+
    "<style>"+
        "h1"+"{"+
            "color:aqua;"+
            "background-color: black;"+
           " text-align: center;"+
          " font-size: 150;"+
            
        "}"+
       " body"+
       "{background-color: dimgrey;}"+
    "</style>"+
"<body>"+
 "<h1>Escritura de datos</h1>"+
 "Analog input:  " + 
 String(analogRead(A0)) +
":"+
"</body>"+
"</html>"+

           
            
            "\r\n";
  return htmlPage;
}
