// Control for HC-SR04 Distance sensor
// Removes FPGA customization and timing problems from cRIO
//


// Trigger, echo, and analog pins
int tp[] = {2, 5, 7, 12};
int ep[] = {4, 6, 8, 13};
int ap[] = {3, 9, 10, 11};

// Dist vector
float dist[] = {0, 0, 0, 0};
int numSens = sizeof(tp)/sizeof(int);

// Returns distance in mm
float findDist(int sens) {
  float duration, distance;
  digitalWrite(tp[sens], LOW);
  delayMicroseconds(2);
  digitalWrite(tp[sens], HIGH);
  delayMicroseconds(10);
  digitalWrite(tp[sens], LOW);
  duration = pulseIn(ep[sens], HIGH);
  distance = (duration / 2) * 0.344;
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
  // Poll the four corners and output data
  for (int i = 0; i < numSens; i++) {
    dist[i] = findDist(i); // in mm
    analogWrite(ap[i], dist[i]); // 0 to 255 value
  }

  // Pause
  delay(100);
} 
