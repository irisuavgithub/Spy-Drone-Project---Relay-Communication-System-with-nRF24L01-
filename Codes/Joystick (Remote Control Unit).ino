//joystick
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define CE_PIN  7
#define CSN_PIN 8

const byte address[6] = "00001";
RF24 radio(CE_PIN, CSN_PIN); 
struct package
{
  int X;
  int Y;
  int Z;
};

typedef struct package Package;
Package data;

void setup() {
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
   digitalWrite(4,HIGH);
  Serial.begin(9600);
  delay(250);
  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MAX);
  radio.openWritingPipe(address);
  radio.stopListening();
}
void loop() {

  radio.write(&data, sizeof(data)); 

  Serial.print("X:");
  Serial.print(data.X);
  Serial.print("    Y:");
  Serial.println(data.Y);
  Serial.print("    Z:");
  Serial.println(data.Z);
  data.X = analogRead(A0);
  data.Y = analogRead(A1);
  data.Z= analogRead(A2);
  delay(2);
bool success = radio.write(&data, sizeof(boolean));

  if (success) {
    digitalWrite(2,HIGH);}
  else {
    digitalWrite(2,LOW);
  }
  


}
