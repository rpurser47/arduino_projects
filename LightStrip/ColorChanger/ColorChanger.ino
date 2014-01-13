#include <PololuLedStrip.h>

// See http://en.wikipedia.org/wiki/HSL_and_HSV
// typedef struct hsv_color_struct
//  {
//    unsigned short int hue;
//    unsigned char saturation, value;
//  } hsv_color;

// Create an ledStrip object and specify pin 12.
PololuLedStrip<12> ledStrip;

// Create a buffer for holding the colors (3 bytes per color).
#define LED_COUNT 60
rgb_color colors[LED_COUNT];


// Converts a color from HSV to RGB.
// hue is a number between 0 and 360.
// saturation is a number between 0 and 255.
// value is a number between 0 and 255.
rgb_color hsvToRgbStruct(short hue, unsigned char saturation, unsigned char value)
{
    if (hue < 0)
    {
      hue += 360;
    }
    if (hue > 359)
    {
      hue-=360;
    }
    uint8_t f = (uint8_t)((float)((hue % 60) * 255) / 60.0);
    uint8_t p = (uint8_t)((float)(value * (255 - saturation)) / 255.0);
    uint8_t q = (uint8_t)((float)(value * (255 - f * saturation / 255)) / 255.0);
    uint8_t t = (uint8_t)((float)(value * (255 - (255 - f) * saturation / 255)) / 255.0);
    uint8_t r = 0, g = 0, b = 0;
    switch((hue / 60) % 6){
        case 0: r = value; g = t; b = p; break;
        case 1: r = q; g = value; b = p; break;
        case 2: r = p; g = value; b = t; break;
        case 3: r = p; g = q; b = value; break;
        case 4: r = t; g = p; b = value; break;
        case 5: r = value; g = p; b = q; break;
    }
    return (rgb_color){r, g, b};
}

void setAllLEDsHSV(unsigned short h,unsigned char s,unsigned char v)
{
  rgb_color newColor = hsvToRgbStruct(h,s,v);
  // ledStrip.write appears to have a bug where it transposes red and green.
  unsigned char temp = newColor.green;
  newColor.green = newColor.red;
  newColor.red = temp;
  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    colors[i] = newColor;
  }
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);  
}

void setAllLEDsRandomValue(unsigned short h)
{
  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    colors[i] = hsvToRgbStruct(h,255,random(255));
  }
  
  // ledStrip.write appears to have a bug where it transposes red and green.
  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    unsigned char temp = colors[i].green;
    colors[i].green = colors[i].red;
    colors[i].red = temp;
  }
 
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);  
}

void setAllLEDsRandomHue(short h, short variation)
{
  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    colors[i] = hsvToRgbStruct(random(h-variation,h+variation),255,255);
  }
  
  // ledStrip.write appears to have a bug where it transposes red and green.
  for(uint16_t i = 0; i < LED_COUNT; i++)
  {
    unsigned char temp = colors[i].green;
    colors[i].green = colors[i].red;
    colors[i].red = temp;
  }
 
  // Write the colors to the LED strip.
  ledStrip.write(colors, LED_COUNT);  
}

short oldHue = 0;
unsigned char oldValue = 0;
void transitionToHue(short newHue,unsigned char newValue,float period)
{
  float numSteps = 100 * period;
  float rateHue = (float)(newHue - oldHue)/numSteps;
  float rateValue = (float)(newValue - oldValue)/numSteps;
  for(unsigned int iStep = 0;iStep < numSteps; iStep++)
  {
    oldHue += rateHue;
    oldValue += newValue;
    setAllLEDsHSV(oldHue,255,oldValue);
    delay(10);
  }
}

void allLEDOff()
{
  oldHue = 0;
  oldValue = 0;
  setAllLEDsHSV(0,0,0);
}
  
void setup() {
  // put your setup code here, to run once:
  allLEDOff();
}

void loop() {
//  for(short h = 0;h < 360;h+=60)
//  {
//    for(unsigned char i = 0;i < 3;i++)
//    { 
   //   setAllLEDsHSV(h,255,255);
    //  short range = (h+30)%60 + 5;
    //  setAllLEDsRandomHue(h,20);
 //   transitionToHue(h,255,1.0);
//      delay(10000);
////    }
//  }

  short h = random(0,359);
  transitionToHue(h,255,1.0);
  delay(5000);
}

