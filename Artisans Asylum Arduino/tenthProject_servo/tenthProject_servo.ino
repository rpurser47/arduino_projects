#include <Servo.h>

Servo myServo;
int buttonPin[] = {2,3,4,5};
int buttonAngle[] = {0,60,120,179};

void setup()
{
  myServo.attach(11);
  for(int i = 0;i < 4;i++)
  {
    pinMode(buttonPin[i],INPUT_PULLUP);
  }
}

void loop()
{
  int targetAngle = -1;
  
  for(int i = 0;i < 4;i++)
  {
    if(digitalRead(buttonPin[i]) == LOW)
    {
      targetAngle = buttonAngle[i];
    }
  }
  if(targetAngle >= 0)
  {
    myServo.write(targetAngle);
  }
}
