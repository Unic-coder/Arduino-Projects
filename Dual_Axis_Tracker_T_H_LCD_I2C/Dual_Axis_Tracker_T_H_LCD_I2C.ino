//Dual Axis Solar tracker by AKIL S (Youtube)
//Buy Now www.featuress.in

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"
#define DHTPIN 12

LiquidCrystal_I2C lcd(0x27,16,2);

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// 180 horizontal MAX
Servo horizontal; // horizontal servo

int servoh = 180; // 90; // stand horizontal servo

int servohLimitHigh = 180;
int servohLimitLow = 65;

Servo vertical; // vertical servo

int servov = 45; // 90; // stand vertical servo

int servovLimitHigh = 120;
int servovLimitLow = 15;


int ldrlt = 0; //LDR top left 

int ldrrt = 1; //LDR Down Left 

int ldrld = 2; //LDR down right 

int ldrrd = 3; //ldr Top rigt 

void setup()
{ 
  Wire.begin();
  Serial.begin(9600);   // Starting Serial Communication Serial

lcd.init();                      // initialize the lcd 
    lcd.backlight();
  dht.begin();


horizontal.attach(9);   // Servo connected to 9th pin Horizontal

vertical.attach(10);     // Servo connected to 10th pin Vertical

horizontal.write(180);   // Set Horizontal Servo to 180 degree

vertical.write(45);      // Set Vertival Servo to 45 degree

delay(3000);     //Delay 3 second

}

void loop() 
{ 
  
  int nDevices = 0;
  

 

  float h = dht.readHumidity();

  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(f)) {
    lcd.print("ERROR");
    return;
  }
 lcd.setCursor(0,0);
 lcd.print("F");
 lcd.setCursor(7,0);
  lcd.print("H");
  
 lcd.setCursor(0,1);
 lcd.print(f);
 lcd.setCursor(7,1);
 lcd.print(h);  

  
  
  int lt = analogRead(ldrlt); // top left

int rt = analogRead(ldrrt); // top right

int ld = analogRead(ldrld); // down left

int rd = analogRead(ldrrd); // down right

// int dtime = analogRead(4)/20; // read potentiometers

// int tol = analogRead(5)/4;

int dtime = 10; int tol = 50;

int avt = (lt + rt) / 2; // average value top

int avd = (ld + rd) / 2; // average value down

int avl = (lt + ld) / 2; // average value left

int avr = (rt + rd) / 2; // average value right

int dvert = avt - avd; // check the diffirence of up and down

int dhoriz = avl - avr;// check the diffirence og left and rigt

Serial.print(avt);

Serial.print(" ");

Serial.print(avd);

Serial.print(" ");

Serial.print(avl);

Serial.print(" ");

Serial.print(avr);

Serial.print(" ");

Serial.print(dtime);

Serial.print(" ");

Serial.print(tol);

Serial.println(" ");

if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle

{

if (avt > avd)

{

servov = ++servov;

if (servov > servovLimitHigh)

{

servov = servovLimitHigh;

}

}

else if (avt < avd)

{

servov= --servov;

if (servov < servovLimitLow)

{

servov = servovLimitLow;

}

}

vertical.write(servov);

}

if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle

{

if (avl > avr)

{

servoh = --servoh;

if (servoh < servohLimitLow)

{

servoh = servohLimitLow;

}

}

else if (avl < avr)

{

servoh = ++servoh;

if (servoh > servohLimitHigh)

{

servoh = servohLimitHigh;

}
}

else if (avl = avr)

{

}

horizontal.write(servoh);

}

delay(dtime);

}
