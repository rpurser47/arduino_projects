int ledPin = 9;
int buttonPin = 5;
int potAnalogPin = 0;
void setup() {                
  pinMode(ledPin, OUTPUT);     
}

// the loop routine runs over and over again forever:
void loop() {
  int reading = analogRead(potAnalogPin)/4;
  analogWrite(ledPin, reading);
}
