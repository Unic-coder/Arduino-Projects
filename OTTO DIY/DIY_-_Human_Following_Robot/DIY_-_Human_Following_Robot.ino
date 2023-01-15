
//Delevoped By Technical Tamizha
//www.Procreativehub.com

#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5 
int Buzzer = 13;
#define Trigger 8 // ultrasonic sensor trigger pin
#define Echo 9 // ultrasonic sensor echo pin
#define IRLeft 7
#define IRRight 6


#include <Otto.h>
Otto Otto;  //This is Otto

long ultrasound() {
   long duration, distance;
   digitalWrite(Trigger,LOW);
   delayMicroseconds(2);
   digitalWrite(Trigger, HIGH);
   delayMicroseconds(10);
   digitalWrite(Trigger, LOW);
   duration = pulseIn(Echo, HIGH);
   distance = duration/58;
   return distance;
}



void setup() {
  Otto.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true,Buzzer); //Set the servo pins and Buzzer pin
  pinMode(Trigger, OUTPUT); 
  pinMode(Echo, INPUT); 
  pinMode(IRLeft, INPUT);
  pinMode(IRRight, INPUT);
  Serial.begin(9600);

}

void loop() {
  int Left_Value = digitalRead(IRLeft);
  int Right_Value = digitalRead(IRRight);
  Serial.println("RIGHT = ");
  Serial.print(IRRight);
    Serial.println("LEFT = ");
  Serial.print(IRLeft);
  
  
  
  if (ultrasound() <=10)
  {
    Otto.walk(1,1000,1);
    }
  else if((Left_Value== 0) && (Right_Value== 1))
  {
    Otto.turn(3,1000,1);
    }
  else if((Left_Value== 1) && (Right_Value== 0))
  {
    Otto.turn(3,1000,-1);
    }
 
    }


void Forward() {
  Otto.walk(1,1000,1);
}

void Backward() {
  Otto.walk(1,1000,-1);
}

void Right(){
  Otto.turn(3,1000,-1);
}

void Left(){
  Otto.turn(3,1000,1);
}

void Stop(){
  Otto.walk(0,1000,1);
  Otto.turn(0,1000,1);
  Otto.walk(0,1000,-1);
  Otto.turn(0,1000,-1);
}
