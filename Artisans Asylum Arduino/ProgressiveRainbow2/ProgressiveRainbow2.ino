int ledPin[] = {11,10,9};
int stepDelayMs = 20;
int colorHoldMs = 2000;

double sequence[9][3] = {0.0, 1.0, 0.0,  //green
                         1.0, 1.0, 0.0,  //yellow
                         0.0, 1.0, 1.0,  //cyan
                         0.0, 0.0, 1.0,  //blue
                         1.0, 0.0, 1.0,  //purple
                         1.0, 1.0, 0.0,  //yellow
                         1.0, 0.0, 0.0,  //red
                         1.0, 0.0, 1.0,  //purple
                         0.0, 1.0, 1.0}; //cyan
                      
double currentLevel[] = {0.0, 0.0, 0.0};  
int nextInSequence = 0;
                      

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

void loop()
{
  Serial.print("From ");
  Serial.print(currentLevel[0]);Serial.print(", ");
  Serial.print(currentLevel[1]);Serial.print(", ");
  Serial.print(currentLevel[2]);Serial.print(" -> ");
  Serial.print(sequence[nextInSequence][0]);Serial.print(", ");
  Serial.print(sequence[nextInSequence][1]);Serial.print(", ");
  Serial.println(sequence[nextInSequence][2]);
  
  // Fade to the next color
  for(int iLevel=0; iLevel<256; iLevel++)
  {
    for(int iLed=0; iLed < 3; iLed++)
    {
      double output = currentLevel[iLed] + ((sequence[nextInSequence][iLed] - currentLevel[iLed]) * double(iLevel) / 255.0);
      analogWrite(ledPin[iLed], 255 - int(output * 255.0));
    }
    delay(stepDelayMs);
  }
  
  // Copy current value to previous value
  for(int iLed = 0; iLed < 3; iLed++)
  {
    currentLevel[iLed] = sequence[nextInSequence][iLed];
  }
  nextInSequence = (nextInSequence + 1) % 9;
  delay(colorHoldMs);
 }
