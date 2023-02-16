
int MOS1 = A0;
int MOS2 = A1;
int MOS3 = A2;


int Data;

int Pmosv1 = 35;
int Pmosv2 = 40;
int Pmosv3 = 44;



void setup()
{
   Serial.begin(9600); 
   pinMode(MOS1,INPUT);
   pinMode(MOS2,INPUT);
   pinMode(MOS3,INPUT);
   pinMode(2,OUTPUT); 
   pinMode(3,OUTPUT);
   pinMode(4,OUTPUT); 
}



void loop()
{
  

 MOS1=1023-analogRead(0);
 MOS1=map(MOS1, 0, 1023, 0, 100);

 MOS2=1023-analogRead(1);
 MOS2=map(MOS2, 0, 1023, 0, 100);

 MOS3=1023-analogRead(2);
 MOS3=map(MOS3, 0, 1023, 0, 100);

 Serial.println("");
 Serial.print ("Plant 1 Moisture Level : ");
 Serial.println(MOS1);
 delay(1000);

 Serial.print("Plant 2 Moisture Level : ");
 Serial.println(MOS2);
 delay(1000);

  
 Serial.print("Plant 3 Moisture Level : ");
 Serial.println(MOS2);
 Serial.println("");
 delay(3000);
 

 if(MOS1 < Pmosv1){       
  digitalWrite(2,HIGH);

  Serial.println("Plant 1 || Motor : ON");
  
  delay(3000);

 }

  if(MOS2 < Pmosv2){       
  digitalWrite(3,HIGH); 
  Serial.println("Plant 2 || Motor : ON");
  delay(3000);

 }

  if(MOS3 < Pmosv3){        
  digitalWrite(4,HIGH); 
  Serial.print("Plant 3 Motor : ON");
  delay(3000);
 
 }

 if(MOS1 > Pmosv1 and MOS2 > Pmosv2 and MOS3 > Pmosv3){
  digitalWrite(2,LOW); 
  Serial.println("");
  Serial.println("Motor 1 : OFF");
  digitalWrite(3,LOW); 
  Serial.println("Motor 2 : OFF");
  digitalWrite(4,LOW); 
  Serial.println("Motor 3 : OFF");
 }



 delay(3000);


}
