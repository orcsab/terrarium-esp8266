/* terrarium-esp8266.ino
 * This sketch drives my NodeMCU controller for my nook-based terrarium.
 */
#include <ESP8266mDNS.h>

#include "TerrServer.h"
#include "NetworkCredentials.h"

// Debug pin for the web server.
const int debugPin = D0;

void setup() {
  Serial.begin(115200);

  TerrServer::init(HOMESSID, HOMEPASSWORD, 80, debugPin);
}

void loop() {
  TerrServer::handleClient();
  MDNS.update();
  Serial.write(".");
  delay(2000);
}
