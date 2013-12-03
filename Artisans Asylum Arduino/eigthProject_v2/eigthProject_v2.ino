void setup()
{
  DDRC = B00111111;
  Serial.begin(9600);
}

void loop()
{
  for(int i = 0; i < 6; i++)
  {
    byte output = byte(pow(2,i))+1;
    PORTC = output;
    Serial.println(output);
    Serial.println(output,BIN);
    delay(100);
  }
  for(int i = 4; i > 0; i--)
  {
    byte output = byte(pow(2,i))+1;
    PORTC = output;
    Serial.println(output,BIN);
    delay(100);
  }
}
