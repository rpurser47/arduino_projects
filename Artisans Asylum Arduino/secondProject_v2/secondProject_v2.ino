int ledPin = 9;
int buttonPin = 5;
int blinkPeriod = 250;
boolean decreasing = true;

void setup() 
{                
  pinMode(ledPin, OUTPUT);     
  pinMode(buttonPin, INPUT_PULLUP);
}

// the loop routine runs over and over again forever:
void loop() 
{
  boolean b = digitalRead(buttonPin);
  if (b == HIGH) 
  {
    blinkPeriod = 250;
  }
  else
  {
    digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(blinkPeriod);               // wait for a second
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    delay(blinkPeriod);               // wait for a second
    if(decreasing)
    {
      blinkPeriod = blinkPeriod - blinkPeriod/5;
    }
    else
    {
      if(blinkPeriod/5 > 1)
      {
        blinkPeriod = blinkPeriod + blinkPeriod/5;
      }
      else
      {
        blinkPeriod++;
      }
    }
    if(decreasing && blinkPeriod <= 5)
    {
      decreasing = false;
    }
    else if(!decreasing && blinkPeriod > 250)
    {
      decreasing = true;
    }
  }
}
