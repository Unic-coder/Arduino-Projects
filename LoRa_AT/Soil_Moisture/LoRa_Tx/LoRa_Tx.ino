/* By Akil S 

Youtube : https://www.youtube.com/@Akilesh-S */


#include <SoftwareSerial.h>

SoftwareSerial lora(2, 3); // RX, TX

#define soil A0 //Moisture to pin A0

float moisture, moisture_percent;
const int AirValue = 620;
const int WaterValue = 310;

void setup() {
  Serial.begin(9600);
  lora.begin(115200);
  pinMode(soil, INPUT);

  lora.println("AT");
  delay(600);
  lora.println("AT+IPR=115200");
  delay(600);
  lora.println("AT+BAND=868500000");
  delay(600);
  lora.println("AT+ADDRESS=1");
  delay(600);
  lora.println("AT+NETWORKID=4");
  delay(600);

}

void loop() {

  moisture = analogRead(soil);
  Serial.println(moisture);
  moisture_percent = map(moisture, AirValue, WaterValue, 0, 100);

  if (moisture_percent <= 30) {
    Serial.println("Low");
    lora.println("AT+SEND=2,2,LO");
    delay(1000);
  } else if (moisture_percent > 31 && moisture_percent < 69) {
    Serial.println("Medium");
    lora.println("AT+SEND=2,2,MI");
    delay(1000);
  } else if (moisture_percent >= 70) {
    Serial.println("High");
    lora.println("AT+SEND=2,2,HI");
    delay(1000);
  }

}