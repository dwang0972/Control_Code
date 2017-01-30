int sensorPin = A0;    // select the input pin for the potentiometer  
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin();
  // declare the ledPin as an OUTPUT:
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.print(sensorValue / 5.03);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);

}
