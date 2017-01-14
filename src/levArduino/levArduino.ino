// Control for HC-SR04 Distance sensor
// Removes FPGA customization and timing problems from cRIO
//

int tp[] = {2, 4, 6};
int ep[] = {3, 5, 7};
int dist[] = {0, 0, 0, 0};
int numSens = sizeof(tp)/sizeof(int);

int ap[] = {10, 11, 12, 13};

long findDist(int sens) {
  long duration, distance;
  digitalWrite(tp[sens], LOW);
  delayMicroseconds(2);
  digitalWrite(tp[sens], HIGH);
  delayMicroseconds(10);
  digitalWrite(tp[sens], LOW);
  duration = pulseIn(ep[sens], HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

void setup() {
  Serial.begin (9600);
  for (int i = 0; i < numSens; i++) {
    pinMode(tp[i], OUTPUT);
    pinMode(ep[i], INPUT);
  }
}

void loop() {
  for (int i = 0; i < numSens; i++) {
    dist[i] = findDist(i); // in cm
    analogWrite(ap[i], dist[i]);
  }
  Serial.println(dist[0]);
  Serial.println(analogRead(A0));
  Serial.println();
  
  delay(1000);
} 
