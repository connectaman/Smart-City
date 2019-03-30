/*
 * Code Written by : Aman Ulla
 */
#include<Servo.h>     //Including the Servo Library
const int pingPin = 10; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 9; // Echo Pin of Ultrasonic Sensor 1 
const int red=3,green=4;         // defining the pins for the led near gate
int ldr=A0;              // defining the analog pin to ldr to read the intensity
int intr=A1;
const int street_light=5;    //defining the pins for led used as street light
const int parking_lights=6;   //defining the pins for led used as parking lights
Servo myServo; // Creating Servo Object
void setup() {
Serial.begin(9600);       // Starting the Serial Monitor at 9600 baud rate
pinMode(red,OUTPUT);    // road 1 signal red set to OUTPUT
pinMode(green,OUTPUT);   //road 2 signal green set to OUTPUT
pinMode(street_light,OUTPUT);  // set the led as OUTPUT
pinMode(parking_lights,OUTPUT); // set the led as OUTPUT
pinMode(intr,INPUT);   // setting interrupt as Input
myServo.attach(13);     // defining the pin number for the servo
myServo.write(0);       // initilization of servo angle to 0 degree
digitalWrite(street_light,LOW);    //initially set the led in off state
digitalWrite(parking_lights,LOW);   //initially set the led in off state
}
void loop() {
 int distance,intensity,interrupt;
 int threshold=200;
 distance=calculatedistance(pingPin,echoPin);   //get the distance
 intensity=get_intensity();   //get the intensity of the surrounding
 interrupt = digitalRead(intr);
 Serial.println("distance"+distance);
 Serial.println("intensity"+intensity);
 if(interrupt==LOW)
 {
  digitalWrite(green,HIGH);
  digitalWrite(red,LOW);
  if(distance < 10)    //checking if there is car near the gate 
  {
  open_gate();
  delay(5000);
  close_gate();
 }
 }
 else{
  digitalWrite(green,LOW);
  digitalWrite(red,HIGH);
 }
 if(intensity<threshold)   //checking if the intensity is lesser than the threshold
 {
   turn_on_light();
 }
 else
  {
    turn_off_light();
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
  meter = cm/100;
  return meter;
} // Function to Open the Gate
void open_gate()
{
  int i;
  for(i=0;i<=180;i++)   //moving the servo hand 180 degree upwards
  {
    myServo.write(i);   
    delay(10);
  }
}
void close_gate()
{
  int i;
  for(i=180;i>=1;i--)   //moving the servo hand 180 degree downwards
  {
    myServo.write(i);
    delay(10);
  }
}
int get_intensity()   //to get the intensity of the surrounding
{
  return analogRead(ldr);
}
void turn_on_light()
{
  digitalWrite(street_light,HIGH);
  digitalWrite(parking_lights,HIGH);
}
void turn_off_light()
{
  digitalWrite(street_light,LOW);
  digitalWrite(parking_lights,LOW);
}
