#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//#define PRINT_DEBUG   //Uncomment this line if you want to print the values on serial monitor

#define SIGNAL_TIMEOUT 500  // This is signal timeout in milli seconds.

const uint64_t pipeIn = 0xF9E8F0F0E1LL;
RF24 radio(7, 8); 
unsigned long lastRecvTime = 0;

struct PacketData
{
  byte xAxisValue;    
  byte yAxisValue;
} receiverData;

//Right motor
int enableRightMotor=9; 
int rightMotorPin1=2;
int rightMotorPin2=3;

//Left motor
int enableLeftMotor=10;
int leftMotorPin1=4;
int leftMotorPin2=5;


void setup()
{
  pinMode(enableRightMotor,OUTPUT);
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);
  
  pinMode(enableLeftMotor,OUTPUT);
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);

  rotateMotor(0,0); 
    
  radio.begin();
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,pipeIn);
  radio.startListening(); //start the radio receiver 

  #ifdef PRINT_DEBUG
    Serial.begin(115200);
  #endif
}

void loop()
{
    int rightMotorSpeed=0;
    int leftMotorSpeed=0;
    // Check if RF is connected and packet is available 
    if(radio.isChipConnected() && radio.available())
    {
      radio.read(&receiverData, sizeof(PacketData)); 
      int mappedYValue = map(receiverData.yAxisValue, 0, 254, -255, 255); 
      int mappedXValue = map(receiverData.xAxisValue, 0, 254, -255, 255); 
      int motorDirection = 1;     
      if (mappedYValue < 0)
      {
        motorDirection = -1;
      }
    
      rightMotorSpeed = abs(mappedYValue) - mappedXValue;
      leftMotorSpeed = abs(mappedYValue) + mappedXValue;
  
      rightMotorSpeed = constrain(rightMotorSpeed, 0, 255);
      leftMotorSpeed = constrain(leftMotorSpeed, 0, 255);
      
      rotateMotor(rightMotorSpeed * motorDirection, leftMotorSpeed * motorDirection);

      lastRecvTime = millis();  
      
      #ifdef PRINT_DEBUG  
        Serial.println(receiverData.xAxisValue);
        Serial.println(receiverData.yAxisValue);      
      #endif
    }
    else
    {
      //Signal lost. Reset the motor to stop
      unsigned long now = millis();
      if ( now - lastRecvTime > SIGNAL_TIMEOUT ) 
      {
        rotateMotor(0, 0);   
     }
   }
}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }
  
  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }  

  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
  }
  
