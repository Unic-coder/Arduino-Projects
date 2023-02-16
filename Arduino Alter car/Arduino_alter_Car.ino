//ARDUINO RC CAR Technical Tamizha

#include <Servo.h>
Servo steering;
int pos = 0; //SERVO POSSITION
int data;

void setup() {
    // put your setup code here, to run once:
  pinMode(2,OUTPUT); //INPUT PIN IN1
  pinMode(3,OUTPUT); //INPUT PIN IN2
  pinMode(4,OUTPUT); //INPUT PN IN3
  pinMode(5,OUTPUT); //INPUT PIN IN4
  pinMode(6,OUTPUT); // BUZZER
  pinMode(7,OUTPUT); //LED
  pinMode(8,OUTPUT); //LED
  steering.attach(12); // SERVO CONNECT TO PIN 11
Serial.begin(9600);


}
void Forward(){
        //RIGHT MOTOR
      digitalWrite(2,HIGH);//MOVE FRONT
      digitalWrite(3,LOW); //MOVE BACK
      //LEFT MOTOR
      digitalWrite(4,LOW);//MOVE BACK
      digitalWrite(5,HIGH);//MOVE FRONT
}
void Backward(){
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
}
void Stop(){
      digitalWrite(2,LOW); 
      digitalWrite(3,LOW);
      digitalWrite(4,LOW); 
      digitalWrite(5,LOW); 
}

void loop() {
    if (Serial.available()){
    data=Serial.read();

    //YOU CAN CHANGE THE data VALUE AS YOUR WISH

    if(data == 'F') //IF LETTER 'A' IS SENT TO BLUETOOTH MOTOR RUNS ANTICLOCKWISE
    {
      Forward();
    }

        if(data == 'B') //IF LETTER 'B' IS SENT TO BLUETOOTH MOTOR RUNS CLOCKWISE
    {
       Backward();
    }

        if(data == 'S') //IF THE BUTTON IS RELEASED THE MOTOR AND BACKLED WILL NOT WORK
    {
      Stop();
      // SERVO MOTOR
      for(pos =90; pos <=90; pos += 1)  // THIS COMMAND IS USED TO BRING BACK SERVO MOTOR IN CENTRE POSSITION
      steering.write(pos);   

      
    }
        if(data == 'L') //IF 'C' IS SENT TO BLUETOOTH SERVO TURNS LEFT SIDE
    {
      for(pos =90; pos <=140; pos += 1)
      steering.write(pos);
      
    }
    if(data == 'R') //SERVO TURNS RIGHT SIDE
    {
      for(pos =90; pos >=30; pos -= 1)
      steering.write(pos);
    }
    if(data == 'M')  //LED ON
    {
      digitalWrite(7,HIGH);
    }
    if(data == 'N') //LED OFF
    {
      digitalWrite(6,HIGH);
    }
    if (data == 'm') //BUZZER ON
    {
      digitalWrite(7,LOW);
    }
    if(data == 'n') //BUZZER OFF
    {
      digitalWrite(6,LOW);
    }
    }
}


    
   
