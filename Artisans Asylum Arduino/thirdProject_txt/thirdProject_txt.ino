int ledPin = 9;
int buttonPin = 5;

void setup() {                
  pinMode(ledPin, OUTPUT);     
  pinMode(buttonPin, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() {
  boolean b = digitalRead(buttonPin);
  if (b == LOW) 
  {
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(250);               // wait for a second
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    delay(250);               // wait for a second
  }
}
