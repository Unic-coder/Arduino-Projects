//Technical Tamizha
//IR - RC Car
//Download IRremote library here: 

#include <IRremote.h>       //Add IRremote library 

int receiverpin = 10; //Connect signal pin to 10

IRrecv irrecv(receiverpin);
decode_results results;

int MotorRF = 2;  
int MotorRB = 3;  
int MotorLF = 4;
int MotorLB = 5;

void Left(){
        //RIGHT MOTOR
      digitalWrite(MotorLB,HIGH);//MOVE FRONT
      digitalWrite(MotorLF,LOW); //MOVE BACK
      //LEFT MOTOR
      digitalWrite(MotorRB,LOW);//MOVE BACK
      digitalWrite(MotorRF,HIGH);//MOVE FRONT
}
void Right(){
      digitalWrite(MotorLB,LOW);
      digitalWrite(MotorLF,HIGH);
      digitalWrite(MotorRB,HIGH);
      digitalWrite(MotorRF,LOW);
}
void Forward(){
      digitalWrite(MotorLB,HIGH);
      digitalWrite(MotorLF,LOW);
      digitalWrite(MotorRB,HIGH);
      digitalWrite(MotorRF,LOW);
}
void Backward(){
      digitalWrite(MotorLB,LOW);
      digitalWrite(MotorLF,HIGH);
      digitalWrite(MotorRB,LOW);
      digitalWrite(MotorRF,HIGH);
}
void Stop(){
      digitalWrite(MotorLB,LOW); 
      digitalWrite(MotorLF,LOW);
      digitalWrite(MotorRB,LOW); 
      digitalWrite(MotorRF,LOW); 
}

void setup() {

  pinMode(receiverpin, INPUT);
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(MotorLF ,OUTPUT); 
  pinMode(MotorRB ,OUTPUT); 
  pinMode(MotorRF ,OUTPUT);
  pinMode(MotorLB ,OUTPUT);

}

void loop() {
  if (irrecv.decode(&results))
  {
    Serial.println(results.value, HEX);
    irrecv.resume();
    
  if (results.value == 0x111){
    Forward();
    
  }

    if (results.value == 0x111){
    Backward();
    
  } 
  
  if (results.value == 0x111){
    Right();
    delay(500);
  }

    if (results.value == 0x111){
    Left();
    delay(500);
  }

    if (results.value == 0x111){
    Stop();
  }
}
}
