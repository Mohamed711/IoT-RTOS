#define SSID "Future Electronics"
#define PASS "11111111"
#define IP "api.thingspeak.com" // thingspeak.com

//String url = "/update?key=OXTX8MVLWRHRDGRK&field1="; //thingspeak channel taking readings
String url = "/talkbacks/3510/commands/160488?api_key=OR8Y2Q84TGE4DII5"; //thingspeak talkback getting info

void setup() {
   Serial2.begin(115200); // for arduino mega
   Serial.begin(115200); //for serial port
   //delay(4000);
          
   while(Serial2.available()>0)
      //Serial.read();
   delay(1000);
       
     Serial.println("AT"); //Testing module
     Serial2.println("AT");

     if(Serial2.find("OK"))
     {
       Serial.println("Module is ready");
     }
     else
     {
       Serial.println("Module have no response.");
     }
 

     Serial2.println("AT+CWMODE=1"); // SETTING mode
     Serial.println("AT+CWMODE=1");
     delay(200);
     if(Serial2.find("OK"))
     {
       Serial.println("Mode set");
     }
     else
     {
       Serial.println("Module have no response.");
     }
     
     while(Serial2.find("OK") == false)
     {
     String wifi="AT+CWJAP=\"";
     wifi+=SSID;
     wifi+="\",\"";
     wifi+=PASS;
     wifi+="\"";
     Serial.println(wifi);
     Serial2.println(wifi);
     delay(5000);
     }
     Serial.println("Connected");

     Serial2.println("AT+CIPMUX=1"); // changing mode
     Serial.println("AT+CIPMUX=1");
     delay(200);
     if(Serial2.find("OK"))
     {
       Serial.println("Mode set");
     }
     else
     {
       Serial.println("Module have no response.");
     }
     Serial.print("Connecting to ");
     Serial.println(IP);
  
     while(Serial2.find("OK") == false)
     {
     String page = "AT+CIPSTART=4,\"TCP\",\"";
     page += IP;
     page += "\",80";
     Serial2.println(page);
     Serial.println(page);
     delay(5000);
     }
     Serial.println("Linked");
}

void loop() {
      int x=analogRead(A0);
    String cmd = "GET ";
     cmd += url;
     //cmd += x;
     cmd += " HTTP/1.1\r\n\r\n";
 
     Serial.print("AT+CIPSEND=4,");//determine how many bytes
     Serial.println(cmd.length());
     Serial2.print("AT+CIPSEND=4,");
     Serial2.println(cmd.length());
   
     if(Serial2.find("OK"))
     {
       Serial.println("OK");
     }else{
       Serial.println("ERROR");
     }

       
       Serial2.print(cmd);//send request
       delay(250);
       
       // delay bta3 el channel 300
       
       while (Serial2.available())
       {
         char c = Serial2.read();
         Serial.write(c);
         if(c=='\r') Serial.print('\n');
       }
       Serial.println("\r\n.............................");
       delay(5000);
       
        while(Serial2.find("OK") == false)
     {
     String page = "AT+CIPSTART=4,\"TCP\",\"";
     page += IP;
     page += "\",80";
     Serial2.println(page);
     Serial.println(page);
     delay(7000);
     }
     Serial.println("Linked");
  }
