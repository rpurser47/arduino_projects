int potAnalogPin = 0;
void setup() {                
  Serial.begin(9600);
  Serial.println("begin");
}

// the loop routine runs over and over again forever:
void loop() {
  int reading = analogRead(potAnalogPin);
  Serial.print("DEC: ");
  Serial.print(reading, DEC);
  Serial.print("\tHEX: ");
  Serial.print(reading, HEX);
  Serial.print("\tBIN: ");
  Serial.println(reading, BIN);
  delay(500);
}
