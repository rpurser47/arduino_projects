#include <Wire.h>
int tmp102Address = 0x48;
int redLedPin = 11;
int blueLedPin = 9;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  pinMode(redLedPin,OUTPUT);
  analogWrite(redLedPin, 255);
  pinMode(blueLedPin,OUTPUT);
  analogWrite(blueLedPin, 255);
}

void loop(){

  float tempInC = getTemperatureFromTMP102(tmp102Address);
  int color = int(tempInC * 100.0);  // gives a int value from 2200 to 2900 or so
  Serial.print("Temp: ");  Serial.print(tempInC);  Serial.print("C");
  int blueColor = map(color,2200,2900,0,255);
  int redColor = 255 - blueColor;
  Serial.print("  Red: ");  Serial.print(redColor);  Serial.print(" Blue: ");  Serial.println(blueColor);
  analogWrite(redLedPin, redColor);
  analogWrite(blueLedPin, blueColor);

  

  delay(200); //just here to slow down the output. You can remove this
}

float getTemperatureFromTMP102(int address){
  Wire.requestFrom(address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  // Serial.print("MSB: ");Serial.print(MSB);Serial.print(" LSB: ");Serial.println(LSB);
  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  return celsius;
}

