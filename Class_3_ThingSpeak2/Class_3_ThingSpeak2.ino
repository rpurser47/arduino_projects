// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino/
// Copyright Rob Purser, 2013

#include <SPI.h>
#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <HttpClient.h>
#include <Wire.h>

unsigned int sdCardSelectPin = 4;

int tmp102Address = 0x48;

// !!! You need to fill in the last byte here
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient client;

// !!! You need to fill in the Write API Key for your ThingSpeak Channel
char writeAPIKey[] = "97KB9882VZOD693P";    


boolean discoSucks = true;

void setup()
{
  Serial.begin(9600);
  Wire.begin();

  // Explicitly deselect the SD card on SPI bus.  This is done by setting pin 4 high.
  // The ethernet interface is unreliable unless this is set high.
  pinMode(sdCardSelectPin, OUTPUT);
  digitalWrite(sdCardSelectPin, HIGH);
  
  // Connect the ethernet, contact DHCP server, and get IP address
  Ethernet.begin(mac);
  Serial.print("Ethernet initialized and assigned address ");Serial.println(Ethernet.localIP());
}

void loop()
{
  float celsius = getTemperature();
  Serial.print("Celsius: ");  Serial.println(celsius);

  // Connect to the server on port 80 (HTTP)
  Serial.println("connecting to ThingSpeak...");
  if (!client.connect("api.thingspeak.com",80))
  { 
    Serial.println("Failed to connect to ThingSpeak...");
    delay(5000);
    return;
  }
  Serial.println("Connected to ThingSpeak...");

  char celsiusStr[20];
  // dtostrf is an undocumented funciton in Arduino that converts a double to a string
  // dtostrf(floatVar, minStringWidthIncDecimalPoint, numVarsAfterDecimal, charBuf);
  dtostrf(celsius, 4, 2, celsiusStr);
  String postData = String("field1=") + String(celsiusStr) + String("\n");
  char postDataStr[100];
  postData.toCharArray(postDataStr, 100);

//    // Post data to thingspeak
//    client.print("POST /update HTTP/1.1\n");
//    client.print("Host: api.thingspeak.com\n");
//    client.print("Connection: close\n");
//    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
//    client.print("Content-Type: application/x-www-form-urlencoded\n");
//    client.print("Content-Length: ");
//    client.print(tsData.length());
//    client.print("\n\n");
//
//    client.print(tsData);client.print("\n");
  HttpClient http(client);

  http.beginRequest();
  if(!http.post("api.thingspeak.com", "/update"))
  {
    Serial.println("post failed");
    client.stop();
    delay(5000);
    return;
  }
  
  http.sendHeader("X-THINGSPEAKAPIKEY", writeAPIKey);
  http.sendHeader("Content-Length", postData.length());
  http.endRequest();
  http.println(postData);
  
  int status = http.responseStatusCode();
  Serial.print("POST returned status of ");Serial.println(status);
  if(status != 200)
  {
    client.stop();
    delay(5000);
    return;
  }
  
  // Ignore the many, many headers, and jump right to the content
  http.skipResponseHeaders();

  // As long as there's data from the server, keep reading it, and mirroring to serial port.
  while (!http.endOfBodyReached())
  {
    Serial.print(char(http.read()));
  }

  // Server has disconnected
  Serial.println();
  Serial.println("disconnecting.");
  client.stop();

  delay(5000);
}

float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //Serial.print("MSB: ");Serial.print(MSB);Serial.print(" LSB: ");Serial.println(LSB);
  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  return celsius;
}

