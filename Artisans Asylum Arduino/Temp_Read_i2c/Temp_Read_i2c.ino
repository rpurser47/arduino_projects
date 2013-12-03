#include <Wire.h>
int tmp102Address = 0x48;

void setup(){
  Serial.begin(9600);
  Wire.begin();
}

void loop(){

  float celsius = getTemperature();
  Serial.print("Celsius: ");  Serial.print(celsius);

  float fahrenheit = (1.8 * celsius) + 32;
  Serial.print("  Fahrenheit: ");  Serial.println(fahrenheit);

  delay(200); //just here to slow down the output. You can remove this
}

float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  // Serial.print("MSB: ");Serial.print(MSB);Serial.print(" LSB: ");Serial.println(LSB);
  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  return celsius;
}

