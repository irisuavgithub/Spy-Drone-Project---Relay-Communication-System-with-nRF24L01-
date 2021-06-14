#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

#define CE_PIN 7
#define CSN_PIN 8

const byte address[6] = "00001";
const byte address2[6]= "00002";
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
  Serial.begin(9600);
  radio.begin(); 
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(0, address);
  radio.openWritingPipe(address2); 
  
}

void loop() {
  radio.startListening();
 
    
    radio.read(&data, sizeof(data));
    Serial.print("Alınan X: ");
    Serial.print(data.X);
    Serial.print("      Alınan Y: ");
    Serial.println(data.Y);
    Serial.print("      Alınan Z: ");
    Serial.println(data.Z);
    
    delay(10);
    
    radio.stopListening();
    delay(10);
    radio.write(&data, sizeof(data));
    Serial.print("Gönderilen X: ");
    Serial.print(data.X);
    Serial.print("      Gönderilen Y: ");
    Serial.println(data.Y);
    Serial.print("      Gönderilen Z: ");
    Serial.println(data.Z);
    
    
    delay(10);
  
}