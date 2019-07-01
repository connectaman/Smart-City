/*
 * Code Written by: Aman Ulla
 */


#include <TinyGPS++.h>    //Import the GPS Library
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial   
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>    //Import Blynk Library
const int slot1=12;   //D6
const int slot2=13;   //D7
const int slot3=14;  // D5

static const int RXPin = 4, TXPin = 5;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800

TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget

SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device

BlynkTimer timer;

float spd;       //Variable  to store the speed
float sats;      //Variable to store no. of satellites response
String bearing;  //Variable to store orientation or direction of GPS

char auth[] = "BLYNK AUTH";              //Your Project authentication key
char ssid[] = "WIFI";                                       // Name of your network (HotSpot or Router name)
char pass[] = "PASSWORD";                                      // Corresponding Password




//unsigned int move_index;         // moving index, to be used later
unsigned int move_index = 1;       // fixed location for now
  

void setup()
{
  Serial.begin(115200);
  Serial.println();
  ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once
}

void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
      Blynk.virtualWrite(V6, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected
  }
  Blynk.virtualWrite(V3, "Empty");
  Blynk.virtualWrite(V4, "Empty");
  Blynk.virtualWrite(V5, "Empty");
}

void loop()
{
 
    while (ss.available() > 0) 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))
        displayInfo();
  }
  int getslot1=digitalRead(slot1);
  int getslot2=digitalRead(slot2);
  int getslot3=digitalRead(slot3);
  if(getslot1==HIGH)
  {
     Blynk.virtualWrite(V3, "Full");
  }
  else
  {
    Blynk.virtualWrite(V3, "Empty");
  }
  if(getslot2==HIGH)
  {
     Blynk.virtualWrite(V4, "Full");
  }
  else
  {
    Blynk.virtualWrite(V4, "Empty");
  }
  if(getslot3==HIGH)
  {
     Blynk.virtualWrite(V5, "Full");
  }
  else
  {
    Blynk.virtualWrite(V5, "Empty");
  }
  Blynk.run();
  timer.run();
}

void displayInfo()
{ 

  if (gps.location.isValid() ) 
  {
    
    float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng()); 
    
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V1, String(latitude, 6));   
    Blynk.virtualWrite(V2, String(longitude, 6));  
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    spd = gps.speed.kmph();               //get speed
//       Blynk.virtualWrite(V3, spd);
       
       sats = gps.satellites.value();    //get number of satellites
       Blynk.virtualWrite(V6, sats);

       bearing = TinyGPSPlus::cardinal(gps.course.value()); // get the direction
//       Blynk.virtualWrite(V5, bearing);               
      
    
  }
  

  Serial.println();
}
