#include<ESP8266WiFi.h>
int sense_pin = 0;
int value = 0;
String apiKey = "your thingspeak API";
const char *ssid = "your wifi name";
const char *pass = "your wifi password";
const char *server = "api.thingspeak.com";
WiFiClient client;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(2000);
  Serial.println("connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid,pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("MOISTURE LEVEL: ");
  value = analogRead(sense_pin);
  value = value/10;
  Serial.println(value);
  delay(1000);
      if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(value);
                             
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}
