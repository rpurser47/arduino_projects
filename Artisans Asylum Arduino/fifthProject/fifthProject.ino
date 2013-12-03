const int redLedPin = 9;
const int greenLedPin = 10;
const int knobAIn = 0;

int readingBuffer[20];
int bufferSize = sizeof(readingBuffer)/sizeof(readingBuffer[0]);
int iNextBufferToWrite = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Started!");
  pinMode(redLedPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);

  int knobReading = analogRead(knobAIn);
  for(int iBuffer = 0 ;iBuffer < bufferSize; iBuffer++)
  {
    readingBuffer[iBuffer] = knobReading;
  }
}

void loop()
{
  int knobReading = analogRead(knobAIn);
  // int ledValue = knobReading/4;
  readingBuffer[iNextBufferToWrite] = knobReading;
  iNextBufferToWrite = (iNextBufferToWrite + 1) % bufferSize;
  int averagedReading = 0;
  for(int iBuffer = 0 ;iBuffer < bufferSize; iBuffer++)
  {
    averagedReading += readingBuffer[iBuffer];
  }
  averagedReading /= bufferSize;
  int redLedValue = map(averagedReading, 970, 1015, 0, 255);
  // analogWrite(ledPin, ledValue);
  Serial.print("Knob Reading: "); Serial.print(knobReading);
  Serial.print(" Averaged Reading: "); Serial.print(averagedReading);
  Serial.print(" LED Output: "); Serial.print(redLedValue);
  Serial.println();
  analogWrite(redLedPin, redLedValue);
  delay(50);
}
