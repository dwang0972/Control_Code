#define trigPin 2
#define echoPin 3
#define analogOut 5
#define analogIn A0

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float duration, distance, rd;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.344;
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" mm");
  analogWrite(analogOut, distance);
  delay(100);
  rd = analogRead(analogIn);
  Serial.print("Read = ");
  Serial.print(rd/4);
  Serial.println(" mm");
  Serial.println();
}
