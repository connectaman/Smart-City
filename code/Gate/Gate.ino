#include<Servo.h>
const int pingPin = 10; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 9; // Echo Pin of Ultrasonic Sensor 
const int red=3,green=4;         // defining the pins for the led near gate
int ldr=A0;              // defining the analog pin to ldr to read the intensity
int light=5;
int street_light=6;
Servo gate;    //creating Servo Class object named gate
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
pinMode(red,OUTPUT);    // road 1 signal red set to OUTPUT
pinMode(green,OUTPUT);   //road 2 signal green set to OUTPUT
pinMode(light,OUTPUT);
pinMode(street_light,OUTPUT);
pinMode(A1,OUTPUT);
digitalWrite(A1,HIGH);
gate.attach(11);     //set pin 6 for servo
gate.write(45);      // set the gate to 0 degree
}

void loop() {
  // put your main code here, to run repeatedly:
int distance,intensity,interrupt=0;
 distance=calculatedistance(pingPin,echoPin);   //get the distance
 intensity = get_intensity();      //get the intensity of the Surrounding
 int threshold=650;
 Serial.print(distance);
 Serial.print("cm");
 Serial.println();
 Serial.print(intensity);
 Serial.print("intensity");
 Serial.println();
 if(intensity<threshold)     //verifying the intensity
 {
  digitalWrite(light,HIGH);   //lights are on
  digitalWrite(street_light,HIGH);
 }
 else
 {
  digitalWrite(light,LOW);   //lights are off
  digitalWrite(street_light,LOW);
 }
 if(distance<8)
 {
  if(distance!=0)
  {
    digitalWrite(light,HIGH);   //lights are on
  digitalWrite(street_light,HIGH);
    digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
  open_gate();
  delay(5000);
  close_gate();
  }
 }
 else
 {
  gate.write(45);         
  digitalWrite(red,HIGH);
  digitalWrite(green,LOW);
 }
}
// Converting millisecond to Centimeter
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
   delay(100);
  return cm;
}
int get_intensity()   //to get the intensity of the surrounding
{
  return analogRead(ldr);
}
void open_gate()
{
  int i;
  for(i=45;i<=120;i++)
  {
    gate.write(i);
    delay(10);
  }
}
void close_gate()
{
  int i;
  for(i=120;i>=45;i--)
  {
    gate.write(i);
    delay(10);
  }
}
