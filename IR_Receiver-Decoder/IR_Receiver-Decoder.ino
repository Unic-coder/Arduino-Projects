//Technical Tamizha
//IR-Decoder

#include <IRremote.h>       //Add IRremote library 

int receiverpin = 10; //Connect signal pin to 10

IRrecv irrecv(receiverpin);
decode_results results;

void setup() {
  pinMode(receiverpin, INPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop() {
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    irrecv.resume();
    delay(150);
  }
}
