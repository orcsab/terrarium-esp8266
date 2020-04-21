/* terrarium-esp8266.ino
 * This sketch drives my NodeMCU controller for my nook-based terrarium.
 */
#include <ESP8266mDNS.h>

#include "NetworkCredentials.h"
#include "TerrServer.h"
#include "TerrDHT11.h"
#include "TerrPhoto.h"

// Debug pin for the web server.
const int debugPin = D0;

// Photo resistor pin
const int photoPin = A0;

// pResistor status pin
const int photoStatusPin = D5;

// DHT11 input pin
const int dhtPin = D2;

void setup() {
  Serial.begin(115200);

  TerrServer::init("terrarium", HOMESSID, HOMEPASSWORD, 80, debugPin);
  TerrPhoto::init(photoPin, photoStatusPin);
  TerrDHT11::init(dhtPin);
}

void loop() {
  TerrPhoto::update();
  TerrDHT11::update();

  TerrServer::handleClient();
  MDNS.update();
  Serial.write(".");
  delay(2000);
}
