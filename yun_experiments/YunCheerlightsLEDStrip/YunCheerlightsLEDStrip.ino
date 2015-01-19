// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino/
// Copyright Rob Purser, 2013

#include <Bridge.h>
#include <HttpClient.h>

#include <PololuLedStrip.h>
// Create an ledStrip object and specify pin 12.
PololuLedStrip<12> ledStrip;
#define LED_COUNT 60
rgb_color colors[LED_COUNT];

// Assume that the serial connection is not available
bool serialEnabled = false;

void setup()
{
  Serial.begin(9600);
  // Provide a indicator that the bridge connection is being set up
  setColor("red");
  Bridge.begin();

  // Provide indicator for serial connection set up
  setColor("yellow");

  // wait up to 5 seconds for the serial interface to start
  long waitStartedAt = millis();
  while(waitStartedAt + 5000 > millis() && !serialEnabled)
  {
    if(!Serial)
    {
      serialEnabled = false;
    }
    else
    {
      serialEnabled = true;
    }
  } 
  // Complete power on self test
  setColor("red");
  delay(500);
  setColor("orange");
  delay(500);
  setColor("yellow");
  delay(500);
  setColor("green");
  delay(500);
  setColor("cyan");
  delay(500);
  setColor("blue");
  delay(500);
  setColor("purple");
  delay(500);
  setColor("pink");
  delay(500);
  setColor("magenta");
  delay(500);
  setColor("white");
  delay(500);
  setColor("oldlace");
  delay(500);
  setColor("none");
}

void loop()
{
  HttpClient client;

  // Make a HTTP request:
    client.get("http://api.thingspeak.com/channels/1417/field/1/last.txt");

  // if there are incoming bytes available 
  // from the server, read them and print them:  
  unsigned int iColor = 0;
  char colorCommand[20];
  while (client.available())
  {
    char c = client.read();
    if(serialEnabled)
    {
      Serial.print(c);
    }
    colorCommand[iColor] = c;
    iColor++;
    if(iColor >= 19)  // remember that C is 0 based, so 19 is the 20th character in the array
    {
      // The text is more than just a color (like an error message) -- stop reading and flush.
      if(serialEnabled)
      {
        Serial.println();
        Serial.println("Got more text than expected -- abandon attempt");
      }
      delay(1000);
      return;
    }
    colorCommand[iColor] = 0;
  }
  if(serialEnabled)
  {
    Serial.println();
    Serial.flush();
    Serial.print("Color was: ");  
    Serial.println(colorCommand);
  }
  setColor(colorCommand);

  delay(5000);
}


unsigned char numColors = 12;
String colorName[] = {
  "none","red","green","blue","cyan","white","warmwhite","oldlace","purple","magenta","pink","yellow","orange"};
int colorRGB[][3] = {  
    0,  0,  0, // "none"
  255,  0,  0, // "red"
    0,255,  0, // "green"
    0,  0,255, // "blue"
    0,255,154, // "cyan",
  255,255,206, // "white",
  255,231,154, // "warmwhite",
  255,231,154, // "oldlace",
  103,  0,154, // "purple",
  255,  0,255, // "magenta",
  255,192,203, // "pink",
  255,255,  0, // "yellow",
  255,128,  0}; // "orange"};  

int colorHSB[][3] = {     
    0,  0,  0, // "none"
    0,255,255, // "red"
  120,255,255, // "green"
  240,255,255, // "blue"
  180,255,255, // "cyan",
    0,  0,255, // "white",
   39,  9, 99, // "warmwhite",
   39,  9, 99, // "oldlace",
  270,255,255, // "purple",
  300,255,255, // "magenta",
  350,206,255, // "pink",
   60,255,255, // "yellow",
   30,255,255}; // "orange"};


void setColor(String color)
{
  for(int iColor = 0; iColor <= numColors; iColor++)
  {
    if(color == colorName[iColor])
    {
      if(serialEnabled)
      {
        Serial.print("Current Color is: "); 
        Serial.println(colorName[iColor]);
      }
      unsigned short hueVariation = 10;
      if(colorHSB[iColor][0] > 345 || colorHSB[iColor][0] < 15)
      {
        hueVariation = 3;
      }
      setAllLEDsVaryingHue(colorHSB[iColor][0], hueVariation, colorHSB[iColor][1], colorHSB[iColor][2]);
      return;
    }
  }
  if(serialEnabled)
  {
    Serial.print("Could not match color: "); 
    Serial.println(color);
  }
}

void setRGB(unsigned short r,unsigned char g,unsigned char b)
{
  rgb_color newColor;
  newColor.red = r;
  newColor.green = g;
  newColor.blue = b;
  
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

