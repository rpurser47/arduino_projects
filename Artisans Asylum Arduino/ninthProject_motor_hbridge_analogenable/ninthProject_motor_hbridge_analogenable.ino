int pinMotorForward = 9;
int pinMotorReverse = 10;
int pinMotorSpeed = 11;

const int off = 0;
const int forward = 1;
const int reverse = 2;
const int brake = 3;

void setup()
{
  Serial.begin(9600);
  Serial.println("Started");
  pinMode(pinMotorForward,OUTPUT); 
  pinMode(pinMotorReverse,OUTPUT); 
  motorSpeedAndDirection(off,0,0);
}

void loop()
{
  motorSpeedAndDirection(forward,100,5000);
  motorSpeedAndDirection(forward,75,5000);
  motorSpeedAndDirection(forward,30,5000);
  motorSpeedAndDirection(brake,0,2000);
  motorSpeedAndDirection(reverse,255,50);
  motorSpeedAndDirection(reverse,30,5000);
  motorSpeedAndDirection(reverse,75,5000);
  motorSpeedAndDirection(reverse,100,5000);
  motorSpeedAndDirection(brake,0,2000);
}

void motorSpeedAndDirection(int direction, int power, int duration)
{
  switch(direction)
  {
    case off:
      digitalWrite(pinMotorReverse, LOW);
      digitalWrite(pinMotorForward, LOW);
      analogWrite(pinMotorSpeed, 0);
      break;
    case forward:
      digitalWrite(pinMotorReverse, LOW);
      digitalWrite(pinMotorForward, HIGH);
      analogWrite(pinMotorSpeed, power);
      break;
    case reverse:
      digitalWrite(pinMotorReverse, HIGH);
      digitalWrite(pinMotorForward, LOW);
      analogWrite(pinMotorSpeed, power);
      break;
    case brake:
      digitalWrite(pinMotorReverse, HIGH);
      digitalWrite(pinMotorForward, HIGH);
      analogWrite(pinMotorSpeed, 255);
      break;
  }
  delay(duration);
  digitalWrite(pinMotorReverse, LOW);
  digitalWrite(pinMotorForward, LOW);
  analogWrite(pinMotorSpeed, 0);
}

