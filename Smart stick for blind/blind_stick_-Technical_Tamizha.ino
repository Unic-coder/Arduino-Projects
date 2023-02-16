//TECHNICAL TAMIZHA
//https://www.procreativehub.com
//Smart Stick for blind People


#define trigPin A0          //sensor A
#define echoPin A1         //sensor A
#define btrigPin A3         //sensor B
#define bechoPin A2         //sensor B
#define BUZZER 2           //BUZZER PIN


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(btrigPin, OUTPUT);
  pinMode(bechoPin, INPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  int bduration, bdistance;
  digitalWrite(btrigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(btrigPin, LOW);
  bduration = pulseIn(bechoPin, HIGH);
  bdistance = (bduration/2) / 29.1;
 
  int duration, distance;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 
  if (distance >= 10 && distance <= 200)      //SET YOUR DISTANCE HERE SENSOR 1
  {

    Serial.print(distance);
    Serial.println(" cm");
    digitalWrite(BUZZER, LOW);
  }
 
 
  else {
     Serial.println("Out of range");
     digitalWrite(BUZZER, HIGH);
     
  }
  if (bdistance >= 11 && bdistance <= 200) //SET YOUR DISTANCE HERE SENSOR 2
  {

    Serial.print(bdistance);
    Serial.println(" cM");
    digitalWrite(BUZZER, LOW);
  }
 
 
  else {
     Serial.println("out of range");
     digitalWrite(BUZZER, HIGH);
     
  }
  delay(50);
}
