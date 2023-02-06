#include <SoftwareSerial.h>      

#include <SD.h>                           //include SD module library
#include <TMRpcm.h>                       //include speaker control library
#define SD_ChipSelectPin 4                //define CS pin
TMRpcm tmrpcm;    

#include "MQ135.h"               
SoftwareSerial esp8266(10,8);      
SoftwareSerial mySerial(2, 3);                 
#define serialCommunicationSpeed 115200       
#define DEBUG true                                 

const int sensorPin= 0;

int air_quality;

#include <LiquidCrystal.h> 

LiquidCrystal lcd(7,A1, A3, A2, A5, A4);

void setup()

{
  Serial.begin(serialCommunicationSpeed);           
  esp8266.begin(serialCommunicationSpeed); 
  mySerial.begin(serialCommunicationSpeed);
  InitWifiModule();    

  tmrpcm.speakerPin = 9;  
  if (!SD.begin(SD_ChipSelectPin)) {      //see if the card is present and can be initialized
    
    return;                               //don't do anything more if not
  }
  tmrpcm.setVolume(1);  
  

  // pinMode(8, OUTPUT);

lcd.begin(16,2);

lcd.setCursor (0,0);

lcd.print (" Setting Up...");

lcd.setCursor (0,1);

lcd.print ("Sensor Warming ");

delay(1000);  

pinMode(sensorPin, INPUT);   

lcd.clear();                        
}

void loop()                                                         
{

MQ135 gasSensor = MQ135(A0);

float air_quality = gasSensor.getPPM();

  if(esp8266.available())                                           
 {    
    if(esp8266.find("+IPD,"))
    {

     int connectionId = esp8266.read()-48; /* We are subtracting 48 from the output because the read() function returns the ASCII decimal value and the first decimal number which is 0 starts at 48*/ 

     String webpage = "<h1>IOT Air Pollution Monitoring System</h1>";

       webpage += "<p><h2>";   

       webpage+= " Air Quality is ";

       webpage+= air_quality;

       webpage+=" PPM";

       webpage += "<p>";

     if (air_quality<=20)

{

  webpage+= "Fresh Air";

}

else if(air_quality<=50 && air_quality>=20)

{

  webpage+= "Poor Air";

}


else if (air_quality>=30 )

{

webpage+= "Danger! Move to Fresh Air";

}


webpage += "</h2></p></body>"; 
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);

//to be================
    cipSend = "AT+CIPSEND=";

     cipSend += connectionId;

     cipSend += ",";

     cipSend +=webpage.length();

     cipSend +="\r\n";
//to be=================
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";    
     sendData(closeCommand,3000,DEBUG);
    }
  }
  lcd.setCursor (0, 0);

lcd.print ("Air Quality is ");

lcd.print (air_quality);

lcd.print (" PPM ");

lcd.setCursor (0,1);

if (air_quality<=20)

{

lcd.print("Fresh Air");

// digitalWrite(8, LOW);

}

else if( air_quality>=50 && air_quality<=30 )

{

lcd.print("Poor Air, Open Windows");

// digitalWrite(8, HIGH );

}

else if (air_quality>=30 )

{

lcd.print("Danger! Move to Fresh Air");
SendMessage();
delay(3000);
SendMessage2();
// digitalWrite(8, HIGH);   // turn the LED on

tmrpcm.setVolume(4);                 
tmrpcm.play("1.wav"); 
delay(11500); 
tmrpcm.setVolume(1);  
}

lcd.scrollDisplayLeft();

delay(1000);
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";                                             
    esp8266.print(command);                                          
    long int time = millis();                                      
    while( (time+timeout) > millis())                                 
    {      
      while(esp8266.available())                                      
      {
        char c = esp8266.read();                                     
        response+=c;                                                  
      }  
    }    
    if(debug)                                                        
    {
      Serial.print(response);
    }    
    return response;                                                  
}

void InitWifiModule()
{
  sendData("AT+RST\r\n", 2000, DEBUG);                                                  
  sendData("AT+CWJAP=\"ESP\",\"wifi0021\"\r\n", 2000, DEBUG);        
  delay (3000);
  sendData("AT+CWMODE=1\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIFSR\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIPMUX=1\r\n", 1500, DEBUG);                                             
  delay (1500);
  sendData("AT+CIPSERVER=1,80\r\n", 1500, DEBUG);   
                        

}


void SendMessage()
{
Serial.println("In send");
mySerial.println("AT+CMGF=1"); 
delay(1000); 
mySerial.println("AT+CMGS=\"9150525618\"\r");
delay(1000);
mySerial.println("Danger! Move to Fresh Air");
delay(100);
mySerial.println((char)26);
delay(1000);
}
void SendMessage2(){
  Serial.println("In send");
mySerial.println("AT+CMGF=1"); 
delay(1000); 
mySerial.println("AT+CMGS=\"9944948773\"\r");
delay(1000);
mySerial.println("Danger! Move to Fresh Air");
delay(100);
mySerial.println((char)26);
delay(1000);

}

void SendMessage3(){

}

