// set pin numbers
const int touchPin = 14; 
const int fan = 12;
const int led = 13;


const int threshold = 20;   // change with your threshold value

int touchValue;             // variable for storing the touch pin value 

void setup(){
  Serial.begin(115200);
  delay(1000);              // time to bring up serial monitor
  
  pinMode (fan, OUTPUT);  
  pinMode(led,OUTPUT);
}

void loop(){
 
  touchValue = touchRead(touchPin);     // read the state of the pushbutton value:
  Serial.print(touchValue);             // check if the touchValue is below the threshold
  
  if(touchValue < threshold){
    
    digitalWrite(fan, HIGH);
    digitalWrite(led, HIGH);
    Serial.println(" - FAN on");
  }
  else{
   
    digitalWrite(fan, LOW);
    digitalWrite(led, LOW);
    Serial.println(" - FAN off");
  }
  delay(100);
}
