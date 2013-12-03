int motorPinForward = 9;
int motorPinReverse = 10;

void setup()
{
  Serial.begin(9600);
  Serial.println("Started");
  pinMode(motorPinForward,OUTPUT); 
  pinMode(motorPinReverse,OUTPUT); 
  digitalWrite(motorPinForward, LOW);
  digitalWrite(motorPinReverse, LOW);
}

void loop()
{
  digitalWrite(motorPinForward, HIGH);
  delay(1000);
  applyBrake();
  digitalWrite(motorPinReverse, HIGH);
  delay(1000);
  applyBrake();
}

void applyBrake()
{
  digitalWrite(motorPinReverse, HIGH);
  digitalWrite(motorPinForward, HIGH);
  delay(2000);
  digitalWrite(motorPinReverse, LOW);
  digitalWrite(motorPinForward, LOW);
}

