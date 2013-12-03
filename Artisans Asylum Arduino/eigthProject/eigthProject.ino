void setup()
{
  DDRC = B00111111;
  
}

void loop()
{
  for(byte i = 0; i < 64; i++)
  {
    PORTC = i;
    delay(100);
  }
  for(byte i = 62; i > 0; i--)
  {
    PORTC = i;
    delay(100);
  }
}
