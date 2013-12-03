int ledPin[] = {9,10,11};
int ledLevels[] = {0,0,0};

void setup()
{
  Serial.begin(9600);
  Serial.println("Started");
  setColor();
  delay(1000);
}

void loop()
{
  ledLevels[0] = 255;
  ledLevels[2] = 255;
  setColor();
  delay(1000);
  ledLevels[0] = 0;
  ledLevels[2] = 0;
  setColor();
  delay(1000);
}

void setColor()
{
  Serial.print("LED is now: ");
  for(int i=0;i<3;i++)
  {
    analogWrite(ledPin[i],255-ledLevels[i]);
    if(ledLevels[i] < 16)
    {
      Serial.print("0");
    }
    Serial.print(ledLevels[i],HEX);
  }
  Serial.println();
}
