int ledPin = 9;
int buttonPin = 5;

void setup() {                
  pinMode(ledPin, OUTPUT);     
  pinMode(buttonPin, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  for(int power = 0;power < 255; power += 1)
  {
    analogWrite(ledPin, power);
    delay(1);               // wait for a second
  }
  delay(500);
  for(int power = 255;power > 0; power -= 1)
  {
    analogWrite(ledPin, power);
    delay(1);               // wait for a second
  }
  delay(500);
}
