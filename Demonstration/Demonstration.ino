// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at http://goo.gl/NNe35. 

int rgbLEDPin[] = {11,10,9};
int stepDelayMs = 20;
int colorHoldMs = 0;

int flickerLEDPin[] = {2,3,4,5};

int knobPin = 0;

double rgbSequence[9][3] = {0.0, 1.0, 0.0,  //green
                         1.0, 1.0, 0.0,  //yellow
                         0.0, 1.0, 1.0,  //cyan
                         0.0, 0.0, 1.0,  //blue
                         1.0, 0.0, 1.0,  //purple
                         1.0, 1.0, 0.0,  //yellow
                         1.0, 0.0, 0.0,  //red
                         1.0, 0.0, 1.0,  //purple
                         0.0, 1.0, 1.0}; //cyan
                         
int ledSequence[10][4] = {HIGH,  LOW,  LOW,  LOW,
                          LOW, HIGH,  LOW,  LOW,
                          LOW,  LOW, HIGH,  LOW,
                          LOW,  LOW,  LOW, HIGH,
                          LOW,  LOW, HIGH,  LOW,
                          LOW, HIGH,  LOW,  LOW,
                         HIGH,  LOW,  LOW,  LOW,
                          LOW,  LOW,  LOW,  LOW,
                          LOW, HIGH,  LOW, HIGH,
                         HIGH,  LOW, HIGH,  LOW};
                      
double currentLevel[] = {0.0, 0.0, 0.0};  
int nextInrgbSequence = 0;
int nextInLEDSequence = 0;
                      

void setup()
{
  Serial.begin(9600);
  Serial.println("Started!");
  for(int i=0; i<3; i++)
  {
    pinMode(rgbLEDPin[i],OUTPUT);
    analogWrite(rgbLEDPin[i], 255);
  }
  for(int i=0; i<4; i++)
  {
    pinMode(flickerLEDPin[i],OUTPUT);
    digitalWrite(flickerLEDPin[i], HIGH);
  }
}

void loop()
{
  Serial.print("From ");
  Serial.print(currentLevel[0]);Serial.print(", ");
  Serial.print(currentLevel[1]);Serial.print(", ");
  Serial.print(currentLevel[2]);Serial.print(" -> ");
  Serial.print(rgbSequence[nextInrgbSequence][0]);Serial.print(", ");
  Serial.print(rgbSequence[nextInrgbSequence][1]);Serial.print(", ");
  Serial.println(rgbSequence[nextInrgbSequence][2]);
  
  // Fade to the next color
  for(int iLevel=0; iLevel<256; iLevel++)
  {
    for(int iLed=0; iLed < 3; iLed++)
    {
      double output = currentLevel[iLed] + ((rgbSequence[nextInrgbSequence][iLed] - currentLevel[iLed]) * double(iLevel) / 255.0);
      analogWrite(rgbLEDPin[iLed], 255 - int(output * 255.0));
    }
    int knobPos = analogRead(knobPin);
    stepDelayMs = map(knobPos,0,1024,5,100);
    delay(stepDelayMs);
    if(iLevel%10 == 0)
    {
      for(int iLed=0; iLed < 4; iLed++)
      {
        digitalWrite(flickerLEDPin[iLed], ledSequence[nextInLEDSequence][iLed]);
      }
      nextInLEDSequence = (nextInLEDSequence + 1) % 10;
    }
  }
  
  // Copy current value to previous value
  for(int iLed = 0; iLed < 3; iLed++)
  {
    currentLevel[iLed] = rgbSequence[nextInrgbSequence][iLed];
  }
  nextInrgbSequence = (nextInrgbSequence + 1) % 9;
  delay(colorHoldMs);
 }
