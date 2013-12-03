int ledPin[] = {11,10,9};
int knobPin[] = {0,1,2};
int cLedPin = sizeof(ledPin)/sizeof(ledPin[0]);

void setup()
{
  Serial.begin(9600);
  Serial.println("Started!");
  for(int iPin = 0;iPin < cLedPin; iPin++)
  {
    pinMode(ledPin[iPin],OUTPUT);
  }
}

void loop()
{
  for(int iPin = 0; iPin < cLedPin; iPin++)
  {
    int knobValue = analogRead(knobPin[iPin]);
    int ledValue = map(knobValue,0,1023,255,0);
    analogWrite(ledPin[iPin], ledValue);
  }
  delay(50);
}
