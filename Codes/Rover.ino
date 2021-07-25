#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 7
#define CSN_PIN 8
const byte address2[6] = "00002";
RF24 radio(CE_PIN, CSN_PIN); 
Servo motor;
struct package
{
  int X;
  int Y;
  int Z;
  int derece;
};

int OUT1 = 4;
int OUT2 = 5;
int OUT3 = 6;
int OUT4 = 9;

typedef struct package Package;
Package data;

void setup() {

  Serial.begin(9600);
  delay(200);

  radio.begin(); 
  radio.setChannel(115); 
  radio.setPALevel(RF24_PA_MAX);
  radio.openReadingPipe(0, address2);
  radio.startListening();
  motor.attach(3);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(OUT3, OUTPUT);
  pinMode(OUT4, OUTPUT);
  analogWrite(OUT1, 0);
  analogWrite(OUT2, 0);
  analogWrite(OUT3, 0);
  analogWrite(OUT4, 0);
  }
void loop() {
 if ( radio.available()) 
  {

    radio.read( &data, sizeof(data) );
  
    Serial.print("X:");
    Serial.print(data.X);
    Serial.print("      Y:");
    Serial.println(data.Y);
    Serial.print("      Z:");
    Serial.println(data.Z);
    int X = data.X;
    int Y = data.Y;
    int Z = data.Z;
    int foward = map(X,492,1024,0,255);
    int backward = map(X,497,0,0,255);
    int right = map(Y,499,1024,0,255);
    int left = map(Y,499,0,0,255);
    int derece = map(Z, 0, 1023, 0, 180);
     motor.write(derece);
    
    if(X < 490 && (Y < 505 && Y > 496)){
      analogWrite(OUT4, backward);
      analogWrite(OUT3, 0);
      analogWrite(OUT2, 0);
      analogWrite(OUT1, backward);
    }else if(X > 524 && (Y < 524 && Y > 490)){
      analogWrite(OUT3, foward);
      analogWrite(OUT4, 0);
      analogWrite(OUT1, 0);
      analogWrite(OUT2, foward); 
    }else if(X < 500 && X > 490 && Y < 500){
      analogWrite(OUT4, left);
      analogWrite(OUT3, 0);
      analogWrite(OUT2, left);
      analogWrite(OUT1, 0);
    }else if(X < 500 && X > 489 && Y > 501){
      analogWrite(OUT4, 0);
      analogWrite(OUT3, right);
      analogWrite(OUT2, 0);
      analogWrite(OUT1, right);
    }
    }
}
