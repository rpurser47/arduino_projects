int ledPin[] = {9,10,11};
int ledLevels[] = {0,0,0};
byte currentColor = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Started");
  setColor();
  delay(1000);
}

void loop()
{
  if(Serial.available() > 0)
  {
    int incoming = Serial.read();
    if (incoming >= '0' && incoming <= '9')
    {
      ledLevels[currentColor] = map(incoming,'0','9',0,255);
      setColor();
      currentColor = ((currentColor + 1) % 3);
    }
  }
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
