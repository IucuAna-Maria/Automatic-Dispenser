#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Initialise Arduino to NodeMCU (10=Rx & 11=Tx)
SoftwareSerial nodemcu(10, 11);

const int PIN_RED   = 4;
const int PIN_GREEN = 3;
const int PIN_BLUE  = 2;

int red;
int green;
int blue;

#define echoPin 5
#define trigPin 6
#define echoPin_ni 7
#define trigPin_ni 8

int relayPin=9;
long duration; // variable for the duration of sound wave travel
float distance; // variable for the distance measurement
long duration_ni;
float distance_ni;
long inch;
float percentage;

void setColor(int R, int G, int B) {
  analogWrite(PIN_RED,   R);
  analogWrite(PIN_GREEN, G);
  analogWrite(PIN_BLUE,  B);
}

void setup() {
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(relayPin, OUTPUT);
  
  Serial.begin(9600);
  nodemcu.begin(9600);
  
  pinMode(trigPin_ni, OUTPUT); // water level trigPin
  pinMode(echoPin_ni, INPUT); // water level echoPin
}

void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.createObject();
  
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  distance = floor(distance * 100) / 100; //Rounding to 2 decimals

  Serial.print("Distanta maini: "); // Displays the distance on the Serial Monitor
  Serial.println(distance);
  delay(1000);

  digitalWrite(trigPin_ni, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin_ni, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin_ni, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration_ni = pulseIn(echoPin_ni, HIGH);
  // Calculating the distance
  distance_ni = duration_ni * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  distance_ni = floor(distance_ni * 100) / 100; //Rounding to 2 decimals

  Serial.print("Distanta nivel lichid: ");
  Serial.println(distance_ni);

  percentage = floor((100 - (distance_ni - 1) * 100 / 8.55) * 100) / 100;
  data["waterLevel"] = percentage;
  Serial.print("PROCENT nivel lichid: ");
  Serial.println(percentage);
  data.printTo(nodemcu);
  jsonBuffer.clear();
  
  delay(1000);

  if(distance < 4 && distance_ni <= 9)
  {
    digitalWrite(relayPin, HIGH);//HIGH for the relay to be on
    delay(500);//For how many milliseconds the Pump works for pumping the liquid(Dispensing quantity)
    digitalWrite(relayPin, LOW);//LOW for the relay to be off
    delay(2000);//Delay after each dispensing
  }
  else
  {
    digitalWrite(relayPin, LOW);
  }

  if (distance_ni >= 1 && distance_ni < 6.98)
  {
    setColor(0, 255, 0); //set LED to Green
  }
  else if (distance_ni >= 6.98 && distance_ni < 8.26)
  {
    setColor(255, 255, 0); //set LED to Yellow
  }
  else if (distance_ni >= 8.26 && distance_ni <= 9)
  {
    setColor(255,165,0); //set LED to Orange
  }
  else if (distance_ni > 9)
  {
    setColor(255, 0, 0);  //set LED to Red
  }

}