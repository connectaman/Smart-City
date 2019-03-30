/* Project :- Traffic Stimulator 
 * Code Written By:- Aman Ulla
 */

const int pingPin = 10; // Trigger Pin of Ultrasonic Sensor 1 (road 1)
const int echoPin = 9; // Echo Pin of Ultrasonic Sensor 1 (road 1)
const int pingPin2 = 12; // Trigger Pin of Ultrasonic Sensor 2 (road 1)
const int echoPin2 = 11; // Echo Pin of Ultrasonic Sensor 2 (road 1)
void setup() {
pinMode(red1,OUTPUT);    // road 1 signal red set to OUTPUT
pinMode(red2,OUTPUT);   // road 2 signal red set to OUTPUT
pinMode(yellow1,OUTPUT);  // road 1 signal yellow set to OUTPUT
pinMode(yellow2,OUTPUT);   // road 2 signal yellow set to OUTPUT
pinMode(green1,OUTPUT);    // road 1 signal green set to OUTPUT
pinMode(green2,OUTPUT);   //road 2 signal green set to OUTPUT
}

void loop() {
  int distance1,distance2;
  
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
}
