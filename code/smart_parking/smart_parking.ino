const int pingPin_1 = 10; // Trigger Pin of Ultrasonic Sensor road_A 1
const int echoPin_1 = 9; // Echo Pin of Ultrasonic Sensor road_A 1
const int pingPin_2 = 5; // Trigger Pin of Ultrasonic Sensor road_A 2
const int echoPin_2 = 6; // Echo Pin of Ultrasonic Sensor road_A 2
const int pingPin_3= 3; // Trigger Pin of Ultrasonic Sensor road_A 2
const int echoPin_3 = 11; // Echo Pin of Ultrasonic Sensor road_A 2
const int slot1 = A0;
const int slot2 = A1;
const int slot3 = A2;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);     // Starting the Serial Communication at 9600 Baud Rate
pinMode(slot1,OUTPUT);
pinMode(slot2,OUTPUT);
pinMode(slot3,OUTPUT);
} 

void loop() {
  // put your main code here, to run repeatedly:
 int distance1=calculatedistance(pingPin_1,echoPin_1);   //get the distance
 Serial.print(distance1);Serial.print("cm Slot 1");
 Serial.println();
 int distance2=calculatedistance(pingPin_2,echoPin_2);   //get the distance
 Serial.print(distance2);Serial.print("cm Slot 2");
 Serial.println();
  int distance3=calculatedistance(pingPin_3,echoPin_3);   //get the distance
 Serial.print(distance3);Serial.print("cm slot 3");
 Serial.println();
 if(distance1 < 10 )
 {
  Serial.println("Slot 1 is full ");
  digitalWrite(slot1,HIGH);
 }
 else {
  Serial.println("Slot 1 is empty ");
  digitalWrite(slot1,LOW);
 }
 if(distance2 < 10 )
 {
  Serial.println("Slot 2 is full ");
  digitalWrite(slot2,HIGH);
 }
 else {
  Serial.println("Slot 2 is empty ");
  digitalWrite(slot2,LOW);
 }
 if(distance3 < 10 )
 {
  Serial.println("Slot 3 is full ");
  digitalWrite(slot3,HIGH);
 }
 else {
  Serial.println("Slot 3 is empty ");
  digitalWrite(slot3,LOW);
 }
 delay(2000);
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
