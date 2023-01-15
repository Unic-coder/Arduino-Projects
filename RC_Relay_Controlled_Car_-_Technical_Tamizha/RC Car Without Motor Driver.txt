//Technical Tamizha
//Arduino RC Car With Relay


int MotorRF = 2;  
int MotorRB = 3;  
int MotorLF = 4;
int MotorLB = 5;

int data;

void Forward(){
  digitalWrite(MotorRF, HIGH);
  digitalWrite(MotorRB, LOW);
  digitalWrite(MotorLF, HIGH);
  digitalWrite(MotorLB, LOW);
}

void Backward(){
    digitalWrite(MotorRF, LOW);
  digitalWrite(MotorRB, HIGH);
  digitalWrite(MotorLF, LOW);
  digitalWrite(MotorLB, HIGH);
}

void Left(){
    digitalWrite(MotorRF, LOW);
  digitalWrite(MotorRB, HIGH);
  digitalWrite(MotorLF, HIGH);
  digitalWrite(MotorLB, LOW);
}

void Right(){
      digitalWrite(MotorRF, HIGH);
  digitalWrite(MotorRB, LOW);
  digitalWrite(MotorLF, LOW);
  digitalWrite(MotorLB, HIGH);
}

void Stop(){
      digitalWrite(MotorRF, LOW);
  digitalWrite(MotorRB, LOW);
  digitalWrite(MotorLF, LOW);
  digitalWrite(MotorLB, LOW);
}

void setup() {
    pinMode(MotorLF ,OUTPUT); 
  pinMode(MotorRB ,OUTPUT); 
  pinMode(MotorRF ,OUTPUT);
  pinMode(MotorLB ,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  if (Serial.available()){
    data=Serial.read();

    if(data == 'F'){
      Forward();
    }
    if(data == 'B'){
      Backward();
    }
    if(data == 'L'){
      Left();
      delay(500);
      Stop();
    }
    if(data == 'R'){
      Right();
      delay(500);
      Stop();
    }
    if(data == 'S'){oooooooii
      Stop();
    }
 
}
}
