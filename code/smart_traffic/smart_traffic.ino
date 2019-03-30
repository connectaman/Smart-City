const int pingPin_A_1 = 10; // Trigger Pin of Ultrasonic Sensor road_A 1
const int echoPin_A_1 = 9; // Echo Pin of Ultrasonic Sensor road_A 1
const int pingPin_A_2 = 5; // Trigger Pin of Ultrasonic Sensor road_A 2
const int echoPin_A_2 = 6; // Echo Pin of Ultrasonic Sensor road_A 2
const int pingPin_B_1= 3; // Trigger Pin of Ultrasonic Sensor road_A 2
const int echoPin_B_1 = 11; // Echo Pin of Ultrasonic Sensor road_A 2
const int red_A = A0;    // road A red signal
const int yellow = A1;   // Road  A and B signal light
const int green_A = A2;   // Road A green signal light
const int red_B=A3;   // Road B red Signal Light
const int green_B=A4;  // Road B green signal Light
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);     // Starting the Serial Communication at 9600 Baud Rate
pinMode(red_A,OUTPUT);
pinMode(red_B,OUTPUT);
pinMode(green_A,OUTPUT);
pinMode(green_B,OUTPUT);
pinMode(yellow,OUTPUT);
digitalWrite(red_A,HIGH);
digitalWrite(red_B,LOW);
digitalWrite(green_A,LOW);
digitalWrite(green_B,LOW);
digitalWrite(yellow,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int decision=0;
 int distance1=calculatedistance(pingPin_A_1,echoPin_A_1);   //get the distance
 Serial.print(distance1);Serial.print("cm Road A 1");
 Serial.println();
 int distance2=calculatedistance(pingPin_A_2,echoPin_A_2);   //get the distance
 Serial.print(distance2);Serial.print("cm Road A 2");
 Serial.println();
  int distance3=calculatedistance(pingPin_B_1,echoPin_B_1);   //get the distance
 Serial.print(distance3);Serial.print("cm Road B 1");
 Serial.println();
 /*
  * Decisions
  *    Road1 AB both less and Road2 less - RoadA more time than Road2
  *    Road1 A less B more and Road2 less - Road A and Road B both same time
  *    
  */
  digitalWrite(red_A,HIGH);
  digitalWrite(green_B,HIGH);
  digitalWrite(red_B,LOW);
  digitalWrite(green_A,LOW);
  digitalWrite(yellow,LOW);
  if(distance3 < 7 && distance1 < 7 && distance2 > 7)
  {
    decision=1;   //normal timing
  }
  if(distance1 < 7 && distance2 > 7 && distance3 < 7)
  {
    decision=1;   //normal timing
  }
  if(distance1 < 7 && distance2 < 7 && distance3 < 7)
  {
    decision=2;   // road A has more vehicle than road B
  }
  if(distance1 > 7 && distance2 > 7 && distance3 < 7)
  {
    decision=3;   //road A is empty and road B has vehicles
  }
   if(distance1 < 7 && distance2 < 7 && distance3 > 7)
  {
    decision=4;   //road B is empty and road A has vehicles
  }
  if(distance1 < 7 && distance2 > 7 && distance3 > 7)
  {
    decision=4;
  }
  
  switch(decision)
  {
    case 1:
      delay(3000); //wait for 3 sec  while road B is green
      digitalWrite(yellow,HIGH);
      digitalWrite(red_A,LOW);
      digitalWrite(green_B,LOW);
      delay(1000);   // wait for 1 sec for yellow signal
      digitalWrite(red_A,LOW);
       digitalWrite(green_B,LOW);
       digitalWrite(red_B,HIGH);
       digitalWrite(green_A,HIGH);
       digitalWrite(yellow,LOW);
       delay(3000);  // wait for 3 sec while the road A is green 
       digitalWrite(yellow,HIGH);
       digitalWrite(red_A,LOW);
       digitalWrite(green_B,LOW);
       digitalWrite(red_B,LOW);
       digitalWrite(green_A,LOW);
       delay(1000);  //  wait for 1 sec for yellow signal
     break;
     case 2:
       delay(3000); //wait for 3 sec  while road B is green
      digitalWrite(yellow,HIGH);
      digitalWrite(red_A,LOW);
      digitalWrite(green_B,LOW);
      delay(1000);   // wait for 1 sec for yellow signal
      digitalWrite(red_A,LOW);
       digitalWrite(green_B,LOW);
       digitalWrite(red_B,HIGH);
       digitalWrite(green_A,HIGH);
       digitalWrite(yellow,LOW);
       delay(6000);  // wait for 6 sec while the road A is green because of rise in density
       digitalWrite(yellow,HIGH);
       digitalWrite(red_A,LOW);
       digitalWrite(green_B,LOW);
       digitalWrite(red_B,LOW);
       digitalWrite(green_A,LOW);
       delay(1000);  //  wait for 1 sec for yellow signal
     break;
     case 3:
      delay(3000); //wait for 3 sec  while road B is green
      digitalWrite(yellow,HIGH);
      digitalWrite(red_A,LOW);
      digitalWrite(green_B,LOW);
      delay(1000);   // wait for 1 sec for yellow signal
      digitalWrite(red_A,LOW);
       digitalWrite(green_B,LOW);
       digitalWrite(red_B,HIGH);
       digitalWrite(green_A,HIGH);
       digitalWrite(yellow,LOW);
       delay(1000);  // wait for 1 sec while the road A is green because road is  empty
       digitalWrite(yellow,HIGH);
       digitalWrite(red_A,LOW);
       digitalWrite(green_B,LOW);
       digitalWrite(red_B,LOW);
       digitalWrite(green_A,LOW);
       delay(1000);  //  wait for 1 sec for yellow signal
     break;
      case 4:
      delay(1000); //wait for 1 sec  while road B is empty
      digitalWrite(yellow,HIGH);
      digitalWrite(red_A,LOW);
      digitalWrite(green_B,LOW);
      delay(1000);   // wait for 1 sec for yellow signal
      digitalWrite(red_A,LOW);
       digitalWrite(green_B,LOW);
       digitalWrite(red_B,HIGH);
       digitalWrite(green_A,HIGH);
       digitalWrite(yellow,LOW);
       delay(3000);  // wait for 3 sec while the road A is green 
       digitalWrite(yellow,HIGH);
       digitalWrite(red_A,LOW);
       digitalWrite(green_B,LOW);
       digitalWrite(red_B,LOW);
       digitalWrite(green_A,LOW);
       delay(1000);  //  wait for 1 sec for yellow signal
     break;
  }
}
long microsecondsToCentimeters(long microseconds)
{
   return microseconds / 29 / 2;
}
//function to calculate the distance using the Sonar
  int calculatedistance(int pingPin , int echoPin){
  long duration, inches, cm,meter;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = microsecondsToCentimeters(duration);
   delay(10);
  return cm;
}
