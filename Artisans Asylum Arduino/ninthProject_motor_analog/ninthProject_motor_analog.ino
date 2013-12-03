int motorPin = 9;

void setup()
{
  Serial.begin(9600);
  Serial.println("Started");
  pinMode(motorPin,OUTPUT); 
  digitalWrite(motorPin, LOW);
}

void loop()
{
  digitalWrite(motorPin, HIGH);
  delay(100);
  digitalWrite(motorPin,LOW);
  delay(2000);
}

