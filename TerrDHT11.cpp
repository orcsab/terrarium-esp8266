/* TerrDHT11.cpp
 * Terrarium wrapper to the DHT11.
 */

#include <DHTesp.h>

#include "TerrDHT11.h"

DHTesp TerrDHT11::_dht;
unsigned int TerrDHT11::_dhtPin;
const char *TerrDHT11::_lastStatus;
TempAndHumidity TerrDHT11::_lastValues {0,0};

// init
// Initialize the DHT11
// pin: the pin to which the DHT11 is attached
void TerrDHT11::init(unsigned int pin) {
  _dhtPin = pin;
  _dht.setup(_dhtPin, DHTesp::DHT11);
  _lastStatus = _dht.getStatusString();
}

// update
// read the DHT11 and store status in this namespace
void TerrDHT11::update () {
  TempAndHumidity current;
  current = _dht.getTempAndHumidity();
  if (current.temperature != NAN)
    _lastValues = current;

  _lastStatus = _dht.getStatusString();
}
