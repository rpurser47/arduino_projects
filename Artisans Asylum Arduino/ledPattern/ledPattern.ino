int redLedPin = 11;
int greenLedPin = 10;
int blueLedPin = 9;

int waveform[100];
int cWaveform = sizeof(waveform)/sizeof(waveform[0]);
int iRedValue = 0;
int iGreenValue = 33;
int iBlueValue = 66;

void setup()
{
  Serial.begin(9600);
  Serial.println("Started!");
  pinMode(redLedPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);
  pinMode(blueLedPin,OUTPUT);
  analogWrite(redLedPin, 255);
  analogWrite(greenLedPin, 255);
  analogWrite(blueLedPin, 255);
  
  for(int iWaveform = 0; iWaveform < cWaveform; iWaveform++)
  {
    waveform[iWaveform] = int((sin(double(6.28)*double(iWaveform)/double(cWaveform)) + 1.00) * 127.0);
    Serial.print("Index ");Serial.print(iWaveform);Serial.print(": ");Serial.println(waveform[iWaveform]);
  }
}

void loop()
{
  analogWrite(redLedPin, waveform[iRedValue]);
  iRedValue = (iRedValue + 1) % cWaveform;
  analogWrite(greenLedPin, waveform[iGreenValue]);
  iGreenValue = (iGreenValue + 1) % cWaveform;
  analogWrite(blueLedPin, waveform[iBlueValue]);
  iBlueValue = (iBlueValue + 1) % cWaveform;
  delay(100);
  analogWrite(greenLedPin, waveform[iGreenValue]);
  iGreenValue = (iGreenValue + 1) % cWaveform;
  analogWrite(blueLedPin, waveform[iBlueValue]);
  iBlueValue = (iBlueValue + 1) % cWaveform;
  delay(100);
  analogWrite(blueLedPin, waveform[iBlueValue]);
  iBlueValue = (iBlueValue + 1) % cWaveform;
  delay(100);
}
