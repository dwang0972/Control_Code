#include <math.h>

int encoder0PinA = 4;
int encoder0PinB = 7;
int encoder0Pos = 0;

int sr = 0.01; // Sample rate (Delay Time)
unsigned long ticks = 16.0; // Number of ticks in the encoder
unsigned long ru = 0; // revolution microseconds
unsigned long t = 0; // Time since start (microseconds)

boolean pA = 0;
boolean pB = 1;
boolean cA = 0;
boolean cB = 0;

void setup() { 
 pinMode (encoder0PinA,INPUT);
 pinMode (encoder0PinB,INPUT);
 Serial.begin (115200);
 t = micros();
} 

void loop() { 
 cA = ((digitalRead(encoder0PinA) == HIGH) && (digitalRead(encoder0PinB) == LOW));
 cB = ((digitalRead(encoder0PinB) == HIGH) && (digitalRead(encoder0PinA) == LOW));
//   Serial.print("cA: ");
//   Serial.println(cA);
//   Serial.print("cB: ");
//   Serial.println(cB);
//   Serial.print("Pos: ");
//   Serial.println(encoder0Pos);
//   Serial.println("");
 if (cA && pB) {
  pA = cA;
  pB = !cA;
  encoder0Pos += 2;
  ru = micros()-t;
  Serial.println(encoder0Pos);
  Serial.println(ru);
  Serial.println("");
  t = micros();
 } else if (cB && pA) {
  pB = cB;
  pA = !cB;
  encoder0Pos += 2;
  ru = micros()-t;
  Serial.println(encoder0Pos);
  Serial.println(ru);
  Serial.println("");
  t = micros();
 }
 delay(sr);
} 
