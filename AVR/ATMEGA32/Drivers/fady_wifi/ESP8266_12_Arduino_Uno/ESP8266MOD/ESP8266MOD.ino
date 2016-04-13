#include <SoftwareSerial.h>
 
SoftwareSerial esp8266(10,11); //make RX Arduino line is pin 2, make TX Arduino line is pin 3.
#define SSID "fady-network"
#define PASS "fatota1112."
#define IP "api.thingspeak.com" // thingspeak.com
String url = "/update?api_key=6SWWF4IE3BLP7VCV&field1="; //thingspeak channel taking readings
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // for arduino mega
  esp8266.begin(115200);
esp8266.println("AT");
Serial.println("AT");

if(esp8266.find("OK"))
{
  Serial.println("module is ready");
}
else
{
  Serial.println("module has no response");
}
delay(300);
//FIRMWARE
esp8266.println("AT+GMR"); // SETTING mode
Serial.println(esp8266.readString());
delay(300);
esp8266.println("AT+CWMODE=1"); // SETTING mode
Serial.println("AT+CWMODE=1"); // SETTING mode

if(esp8266.find("OK"))
{
  Serial.println("mode is set");
}
else
{
  Serial.println("module habe no response");
}
delay(300);

while(esp8266.find("OK") == false)
{
String wifi="AT+CWJAP=\"";
wifi+=SSID;
wifi+="\",\"";
wifi+=PASS;
wifi+="\"";
Serial.println(wifi);
esp8266.println(wifi);
delay(5000);
}
Serial.println("Connected");
esp8266.println("AT+CIPMUX=1"); // changing mode
Serial.println("AT+CIPMUX=1"); // changing mode
delay(200);
if(esp8266.find("OK"))
{
  Serial.println("mode is set");
}
else
{
  Serial.println("module habe no response");
}
Serial.print("Connecting to ");
Serial.println(IP);
delay(300);
while(esp8266.find("OK") == false)
{
String page = "AT+CIPSTART=4,\"TCP\",\"";

page += IP;
page += "\",80";
esp8266.println(page);
Serial.println(page);
delay(5000);
}
Serial.println("Linked");
  
}
//
//
void loop() {
 int x=analogRead(A0);
String cmd = "GET ";
cmd += url;
cmd += x;
cmd += " HTTP/1.0\r\n\r\n";
esp8266.print("AT+CIPSEND=4,");
Serial.print("AT+CIPSEND=4,");
esp8266.println(cmd.length());
Serial.println(cmd.length());
if(esp8266.find("OK"))
{
  Serial.println("OK");
}
else
{
  Serial.println("ERROR");
}
esp8266.print(cmd);
delay(250);
while(esp8266.available())
{
char c = esp8266.read();
Serial.write(c);
if(c=='\r') Serial.print('\n');
}
Serial.println("\r\n.............................");
delay(5000);

while(esp8266.find("OK") == false)
{
String page = "AT+CIPSTART=4,\"TCP\",\"";
page += IP;
page += "\",80";
esp8266.println(page);
Serial.println(page);
delay(7000);
}
Serial.println("Linked");
  // put your main code here, to run repeatedly:

}
