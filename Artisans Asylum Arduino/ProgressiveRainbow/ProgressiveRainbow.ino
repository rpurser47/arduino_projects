int ledPin[] = {11,10,9};
int stepDelayMs = 20;
int colorHoldMs = 2000;

void setup()
{
  Serial.begin(9600);
  Serial.println("Started!");
  for(int i=0; i<3; i++)
  {
    pinMode(ledPin[i],OUTPUT);
    analogWrite(ledPin[i], 255);
  }
  
  // Green up
  Serial.println("Green up");
  for(int i=255; i>=0; i--)
  {
    analogWrite(ledPin[1], i);
    delay(stepDelayMs);
  }
  delay(colorHoldMs);
}

void loop()
{
  // Blue up -> Cyan
  Serial.println("Blue up -> Cyan");
  for(int i=255; i>=0; i--)
  {
    analogWrite(ledPin[2], i);
    delay(stepDelayMs);
  }
  delay(colorHoldMs);
  
  // Green down -> Blue
  Serial.println("Green down -> Blue");
  for(int i=0; i<256; i++)
  {
    analogWrite(ledPin[1], i);
    delay(stepDelayMs);
  }
  delay(colorHoldMs);
  
  // Red up -> Purple
  Serial.println("Red up -> Purple");
  for(int i=255; i>=0; i--)
  {
    analogWrite(ledPin[0], i);
    delay(stepDelayMs);
  }
  delay(colorHoldMs);
  
  // Blue down -> Red
  Serial.println("Blue down -> Red");
  for(int i=0; i<256; i++)
  {
    analogWrite(ledPin[2], i);
    delay(stepDelayMs);
  }
  delay(colorHoldMs);
  
  // Green up -> Yellow
  Serial.println("Green up -> Yellow");
  for(int i=255; i>=0; i--)
  {
    analogWrite(ledPin[1], i);
    delay(stepDelayMs);
  }
  delay(colorHoldMs);
  
  // Red down -> Green
  Serial.println("Red down -> Green");
  for(int i=0; i<256; i++)
  {
    analogWrite(ledPin[0], i);
    delay(stepDelayMs);
  }
  delay(colorHoldMs);
}
