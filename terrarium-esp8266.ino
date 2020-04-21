/* terrarium-esp8266.ino
 * This sketch drives my NodeMCU controller for my nook-based terrarium.
 */
#include <ESP8266mDNS.h>

#include "TerrServer.h"
#include "NetworkCredentials.h"
#include "TerrPhoto.h"

// Debug pin for the web server.
const int debugPin = D0;

// Photo resistor pin
const int photoPin = A0;

void setup() {
  Serial.begin(115200);

  TerrServer::init("terrarium", HOMESSID, HOMEPASSWORD, 80, debugPin);
  TerrPhoto::init(photoPin);
}

void loop() {
  TerrPhoto::update();
  TerrServer::handleClient();
  MDNS.update();
  Serial.write(".");
  delay(2000);
}
