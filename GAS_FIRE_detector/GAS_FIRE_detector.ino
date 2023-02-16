#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(9, 10);



int sensorPin = A1;
int sensorValue = 0; 
int gasValue = A0; 
int data;
 
void setup()
{
randomSeed(analogRead(0));
mySerial.begin(9600);
Serial.begin(9600); 
lcd.begin(16,2);
pinMode(gasValue, INPUT);
lcd.print ("Gas / Fire");
lcd.setCursor(0,1);
lcd.print (" Detector Alarm ");
delay(3000);
lcd.clear();
}
 
void loop()
{

sensorValue = analogRead(sensorPin);
 
data = analogRead(gasValue);
Serial.println("Fire");
Serial.println(sensorValue);
Serial.print("Gas Level: ");
Serial.println(data);
lcd.print ("Gas Scan is ON");
lcd.setCursor(0,1);
lcd.print("Gas Level: ");
lcd.print(data);
delay(1000);

if (sensorValue < 100)
{
  SendMessageF();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Fire!!!");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(1000);
}
  
if ( data > 500) //
{
SendMessage();
Serial.print("Gas/Fire detect alarm");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Exceed");
lcd.setCursor(0,1);
lcd.print("SMS Sent");
delay(1000);
 
}
else
{
Serial.print("Gas/Fire Level Low");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Normal");
lcd.setCursor(0,1);
lcd.print("No Fire Detected");
delay(1000);
}
 
lcd.clear();
}
 
void SendMessage()
{
Serial.println("In send");
mySerial.println("AT+CMGF=1"); 
delay(1000); 
mySerial.println("AT+CMGS=\"number\"\r");
delay(1000);
mySerial.println("Excess Gas Detected");
delay(100);
mySerial.println((char)26);
delay(1000);
}

void SendMessageF()
{
Serial.println("In send");
mySerial.println("AT+CMGF=1"); 
delay(1000); 
mySerial.println("AT+CMGS=\"number\"\r"); 
delay(1000);
mySerial.println("Fire Allert!!!Call 102");
delay(100);
mySerial.println((char)26);
delay(1000);
}
