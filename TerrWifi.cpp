/* TerrWifi.cpp
 * Wifi functionality.
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include "TerrWifi.h"
/* init
 * Initialize the wifi.
 */
void TerrWifi::init (const char *name, const char *ssid, const char *pass) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin(name)) {
    Serial.println("MDNS responder started");
  }
}
