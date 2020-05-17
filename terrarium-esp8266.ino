/* terrarium-esp8266.ino
 * This sketch drives my NodeMCU controller for my nook-based terrarium.
 */
#include <ESP8266mDNS.h>
#include <NTPClient.h>
#include <WifiUdp.h>

#include "NetworkCredentials.h"
#include "TerrWifi.h"
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

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = 28800;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D5, OUTPUT);

  TerrWifi::init("terrarium", HOMESSID, HOMEPASSWORD);
  //TerrServer::init(80, debugPin);
  //TerrPhoto::init(photoPin, photoStatusPin);
  //TerrDHT11::init(dhtPin);

  timeClient.begin();
}

void loop() {
  timeClient.update();
  //TerrPhoto::update();
  //TerrDHT11::update();

  //TerrServer::handleClient();
  MDNS.update();

  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());

  if (timeClient.getMinutes() % 2)
    digitalWrite(D5, HIGH);
  else
    digitalWrite(D5, LOW);

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
}
