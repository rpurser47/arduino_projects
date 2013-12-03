const int redLed = 2;
const int yellowLed = 3;
const int greenLed = 4;
const int onTimeInMs = 250;
const int offTimeInMs = 250;

void setup()
{
  pinMode(redLed,OUTPUT);
  pinMode(yellowLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
}

void loop()
{
  digitalWrite(redLed, HIGH);
  delay(onTimeInMs);
  digitalWrite(redLed, LOW);

  digitalWrite(yellowLed, HIGH);
  delay(onTimeInMs);
  digitalWrite(yellowLed, LOW);

  digitalWrite(greenLed, HIGH);
  delay(onTimeInMs);
  digitalWrite(greenLed, LOW);
}
