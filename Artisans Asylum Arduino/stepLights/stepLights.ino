const int redLed = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int inSwitch = 12;
const int onTimeInMs = 250;
const int offTimeInMs = 250;
int currentLed = 0;

void setup()
{
  pinMode(redLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
  pinMode(inSwitch,INPUT);
}

void loop()
{
  switch(currentLed)
  {
    case 0:
      digitalWrite(redLed, HIGH);
      break;
    case 1:
      digitalWrite(yellowLed, HIGH);
      break;
    case 2:
      digitalWrite(greenLed, HIGH);
      break;
  }
  delay(onTimeInMs);
  while(digitalRead(inSwitch)==LOW) {}  // WAit for button press
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, LOW);
  currentLed = (currentLed+1) % 3;
}
