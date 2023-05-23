/* By Akil S 

Youtube : https://www.youtube.com/@Akilesh-S */

#include <SoftwareSerial.h>

SoftwareSerial lora(2, 3); // RX, TX

String incomming;

#define motor 4   //Relay to pin 4

void setup() {
  Serial.begin(9600);
  lora.begin(115200);

  pinMode(motor, OUTPUT);

  lora.println("AT");
  delay(1000);
  lora.println("AT+IPR=115200");
  delay(600);
  lora.println("AT+BAND=868500000");
  delay(600);
  lora.println("AT+ADDRESS=2");
  delay(600);
  lora.println("AT+NETWORKID=4");
  delay(600);

}

void loop() {
  if (lora.available()) {
    incomming = lora.readString();
    if (incomming.indexOf("LO") > 0) {
      digitalWrite(motor, HIGH);
      Serial.println("LO");
    } else if (incomming.indexOf("MI") > 0) {
      //  digitalWrite(motor,HIGH);
      Serial.println("MI");
    } else if (incomming.indexOf("HI") > 0) {
      digitalWrite(motor, LOW);
      Serial.println("HI");

    }
  }

}