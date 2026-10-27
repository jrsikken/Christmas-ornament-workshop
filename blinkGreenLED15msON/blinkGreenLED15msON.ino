#include <Adafruit_TinyUSB.h>  // Adding this initializes USB more reliable and Windows keeps seeing a COM port

const int rode_led = 0;
const int groene_led = 1;
const int blauwe_led = 2;
const int ground = 3;

void setup() { // the setup function runs once
  pinMode(rode_led, OUTPUT);
  pinMode(groene_led, OUTPUT);
  pinMode(blauwe_led, OUTPUT);
  pinMode(ground, OUTPUT);

  digitalWrite(rode_led, 0);
  digitalWrite(groene_led, 0);
  digitalWrite(blauwe_led, 0);
  digitalWrite(ground, 0);
  Serial.begin(115200); // Adding this initializes USB more reliable and Windows keeps seeing a COM port
}

void loop() { // the loop function runs over and over again            
  digitalWrite(groene_led, 1); 
  delay(15);  
  digitalWrite(groene_led, 0);             
  delay(1000);             
}