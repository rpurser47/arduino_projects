#include <Wire.h>
int tmp102Address = 0x48;
int redLedPin = 11;
int greenLedPin = 10;
int blueLedPin = 9;
unsigned long timeCalStarted;
float minTempInF = 1000;
float maxTempInF = 0;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  pinMode(redLedPin,OUTPUT);
  analogWrite(redLedPin, 255);
  pinMode(blueLedPin,OUTPUT);
  analogWrite(blueLedPin, 255);
  pinMode(greenLedPin,OUTPUT);
  analogWrite(greenLedPin, 255);
  timeCalStarted = millis();
}

void loop(){

  float tempInF = getTempInFFromTMP102(tmp102Address);
  if(tempInF < minTempInF)
  {
    timeCalStarted = millis();
    minTempInF = tempInF;
  }
  if(tempInF > maxTempInF)
  {
    timeCalStarted = millis();
    maxTempInF = tempInF;
  }
  Serial.print("Min: ");  Serial.print(minTempInF);  Serial.print("F");
  Serial.print(" Temp: ");  Serial.print(tempInF);  Serial.print("F");
  Serial.print(" Max: ");  Serial.print(maxTempInF);  Serial.print("F");
  int blueColor = map(int(tempInF * 100.0),int(minTempInF * 100.0),int(maxTempInF * 100.0),0,255);
  int redColor = 255 - blueColor;
  Serial.print("  Red: ");  Serial.print(redColor);  Serial.print(" Blue: ");  Serial.println(blueColor);
  
  blueColor = constrain(blueColor,0,255);
  redColor = constrain(redColor,0,255);
  
  if(millis() - timeCalStarted < 5000)
  {
    analogWrite(redLedPin, 255);
    analogWrite(greenLedPin, 0);
    analogWrite(blueLedPin, 255);
  }
  else
  {
    analogWrite(redLedPin, redColor);
    analogWrite(greenLedPin, 255);
    analogWrite(blueLedPin, blueColor);
  }
  

  delay(200); //just here to slow down the output. You can remove this
}

float getTempInFFromTMP102(int address){
  Wire.requestFrom(address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  // Serial.print("MSB: ");Serial.print(MSB);Serial.print(" LSB: ");Serial.println(LSB);
  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  float fahrenheit = (1.8 * celsius) + 32;
  return fahrenheit;
}

