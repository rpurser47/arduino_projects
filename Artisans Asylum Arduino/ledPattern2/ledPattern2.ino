int ledPin[] = {11,10,9};

void setup()
{
  Serial.begin(9600);
  Serial.println("Started!");
  for(int i=0; i<3; i++)
  {
    pinMode(ledPin[i],OUTPUT);
    analogWrite(ledPin[i], 255);
  }
}

int ledCurrent[3] = {20,5,20};

void loop()
{
  int ledTarget[3] = {0,0,0};
  int primaryLed = 0;
  int secondaryLed = 0;
  switch(random(0,3))
  {
    case 0:
      // One light
      ledTarget[random(0,3)]= random(50,255);
      break;
    case 1:
      // Two lights
      while(primaryLed == secondaryLed)
      {
        primaryLed = random(0,3);
        secondaryLed = random(0,3);
      }
      ledTarget[primaryLed]= random(50,100);
      ledTarget[secondaryLed]= random(0,50);
      break;
    case 2:
      // Three lights
      int target = random(50,100);
      for(int iLed = 0;iLed < 3;iLed++)
      {
        ledTarget[iLed] = target;
      }
      break;
  }
  
  // The green is very powerful, run at 25% of power
  ledTarget[1] /=4;
  
  Serial.print("RGB: ");
  Serial.print(ledCurrent[0]); Serial.write(", ");
  Serial.print(ledCurrent[1]); Serial.write(", ");
  Serial.print(ledCurrent[2]);
  Serial.print("->");
  Serial.print(ledTarget[0]); Serial.write(", ");
  Serial.print(ledTarget[1]); Serial.write(", ");
  Serial.println(ledTarget[2]);

  for(int i = 1;i <= 100; i++)
  {
    for(int iLed = 0;iLed < 3;iLed++)
    {
      analogWrite(ledPin[iLed], 255 - ledCurrent[iLed] + int(double(ledCurrent[iLed] - ledTarget[iLed]) * double(i)/100.0));
    }
    delay(50);
  }
  delay(4000);
  for(int iLed = 0;iLed < 3;iLed++)
  {
    ledCurrent[iLed] = ledTarget[iLed];
  }
}
