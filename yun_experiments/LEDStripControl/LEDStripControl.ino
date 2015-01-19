#include <Bridge.h>

#include <PololuLedStrip.h>
// Create an ledStrip object and specify pin 12.
PololuLedStrip<12> ledStrip;

unsigned short setting[3];
unsigned short hueSetting = 0;
unsigned char saturationSetting = 0;
unsigned char brightnessSetting = 0;
long lastChangedAt;

void setup()
{
  Serial.begin(9600);
  setAllLEDsHSB(0,0,0);
  setting[0] = 0;
  setting[1] = 0;
  setting[2] = 0;
  lastChangedAt = millis();
}

int pinIndex = 0;

void loop()
{
  if(Serial.available() > 0)
  {
    while(Serial.available() > 0)
    {
      int command = 0;
      int hundredsDigit = 48;
      if(pinIndex == 0)
      {
        // Read the hundred digit from serial port (for hue only)
        hundredsDigit = Serial.read();   
        // Ignore anything except ASCII 48 to 57, '0' to '9'
        if(hundredsDigit < 48 || hundredsDigit > 57)
        {
          if(hundredsDigit == 13)
          {
            // reset if it was carrage return
            pinIndex = 0;
          }
          continue;
        }
        // Translate '0' to 0, '1' to 100, etc.
        command = map(hundredsDigit,48,57,0,900);
      }

      // Read the tens digit from serial port
      int tensDigit = Serial.read();   
      // Ignore anything except ASCII 48 to 57, '0' to '9'
      if(tensDigit < 48 || tensDigit > 57)
      {
        if(tensDigit == 13)
        {
          // reset if it was carrage return
          pinIndex = 0;
        }
        continue;
      }
      // Translate '0' to 0, '9' to 90, etc.
      command = command + map(tensDigit,48,57,0,90);

      // Read the ones digit from serial port
      int onesDigit = Serial.read();   
      // Ignore anything except ASCII 48 to 57, '0' to '9'
      if(onesDigit < 48 || onesDigit > 57)
      {
        if(onesDigit == 13)
        {
          // reset if it was carrage return
          pinIndex = 0;
        }
        continue;
      }
      // Translate '0' to 0, '9' to 9, etc.
      command = command + map(onesDigit,48,57,0,9);
      setting[pinIndex] = command;
      
      // Print out the command
      if(pinIndex == 0)
      {
        Serial.print((char)hundredsDigit);
      }
      Serial.print((char)tensDigit);Serial.print((char)onesDigit);
      
      pinIndex = (pinIndex + 1) % 3;
    }
    hueSetting = setting[0];
    saturationSetting = map(setting[1],0,99,0,255);
    brightnessSetting = map(setting[2],0,99,0,255);
    Serial.print(": Setting strip to ");
    Serial.print(hueSetting); Serial.print(", ");
    Serial.print(saturationSetting); Serial.print(", ");
    Serial.println(brightnessSetting);
    setAllLEDsVaryingHue(hueSetting,10,saturationSetting,brightnessSetting);
    lastChangedAt = millis();
  }
  if(lastChangedAt + 1000 < millis() && brightnessSetting != 0)
  {
    unsigned short hueVariation = 10;
    if(hueSetting > 345 || hueSetting < 15)
    {
      hueVariation = 3;
    }
    setAllLEDsVaryingHue(hueSetting,hueVariation,saturationSetting,brightnessSetting);
    lastChangedAt = millis();
  }

}

#define LED_COUNT 60
rgb_color colors[LED_COUNT];

// Converts a color from HSB to RGB.
// hue is a number between 0 and 360.  Values outside the range are accepted, and moved into the range
// saturation is a number between 0 and 255.
// brightness is a number between 0 and 255.
rgb_color hsbToRgbStruct(short hue, unsigned char saturation, unsigned char brightness)
{
    // see http://www.cs.rit.edu/~ncs/color/t_convert.html
    if (hue < 0)
    {
      hue += 360;
    }
    if (hue > 359)
    {
      hue-=360;
    }
    uint8_t f = (uint8_t)((float)((hue % 60) * 255) / 60.0);
    uint8_t p = (uint8_t)((float)(brightness * (255 - saturation)) / 255.0);
    uint8_t q = (uint8_t)((float)(brightness * (255 - f * saturation / 255)) / 255.0);
    uint8_t t = (uint8_t)((float)(brightness * (255 - (255 - f) * saturation / 255)) / 255.0);
    uint8_t r = 0, g = 0, b = 0;
    switch((hue / 60) % 6){
        case 0: r = brightness; g = t; b = p; break;
        case 1: r = q; g = brightness; b = p; break;
        case 2: r = p; g = brightness; b = t; break;
        case 3: r = p; g = q; b = brightness; break;
        case 4: r = t; g = p; b = brightness; break;
        case 5: r = brightness; g = p; b = q; break;
    }
    return (rgb_color){r, g, b};
}

void setAllLEDsHSB(short h,unsigned char s,unsigned char b)
{
  rgb_color newColor = hsbToRgbStruct(h,s,b);
  // ledStrip.write appears to have a bug where it transposes red and green.
  unsigned char temp = newColor.green;
  newColor.green = newColor.red;
  newColor.red = temp;
  // The blue LEDs are brighter than the other two -- scale to 80%.
  newColor.blue = newColor.blue * .8;
  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    colors[i] = newColor;
  }
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);  
}

void setAllLEDsVaryingHue(unsigned short h, unsigned short hueVariation,unsigned char s,unsigned char b)
{
  // It's OK for maxHue and minHue to be out of range, the hsbToRgbStruct will coerce them correctly.
  short maxHue = h + hueVariation;  
  short minHue = h - hueVariation;

  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    colors[i] = hsbToRgbStruct(random(minHue,maxHue),s,b);
    // ledStrip.write appears to have a bug where it transposes red and green.
    unsigned char temp = colors[i].green;
    colors[i].green = colors[i].red;
    colors[i].red = temp;
    // The blue LEDs are brighter than the other two -- scale to 80%.
    colors[i].blue = colors[i].blue * .8;
  }
 
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);  
}

void setAllLEDsVaryingSaturation(short h,unsigned char s, short saturationVariation,unsigned char b)
{
  short maxSaturation = s + saturationVariation;
  if(maxSaturation > 255)
  {
    maxSaturation = 255;
  }
    
  short minSaturation = s - saturationVariation;
  if(minSaturation < 0)
  {
    minSaturation = 0;
  }

  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    colors[i] = hsbToRgbStruct(h,random(minSaturation,maxSaturation),b);
    // ledStrip.write appears to have a bug where it transposes red and green.
    unsigned char temp = colors[i].green;
    colors[i].green = colors[i].red;
    colors[i].red = temp;
    // The blue LEDs are brighter than the other two -- scale to 80%.
    colors[i].blue = colors[i].blue * .8;
  }
 
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);  
}

void setAllLEDsVaryingBrightness(short h,unsigned char s,unsigned char b, short brightnessVariation)
{
  short maxBrightness = b + brightnessVariation;
  if(maxBrightness > 255)
  {
    maxBrightness = 255;
  }
    
  short minBrightness = b - brightnessVariation;
  if(minBrightness < 0)
  {
    minBrightness = 0;
  }

  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    colors[i] = hsbToRgbStruct(h,s,random(minBrightness,maxBrightness));
    // ledStrip.write appears to have a bug where it transposes red and green.
    unsigned char temp = colors[i].green;
    colors[i].green = colors[i].red;
    colors[i].red = temp;
    // The blue LEDs are brighter than the other two -- scale to 80%.
    colors[i].blue = colors[i].blue * .8;
  }
 
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);  
}

