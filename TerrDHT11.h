/* TerrDHT11.h
 * Interface to the DHT11 I'm using for the terrarium.
 */

 #ifndef _TERRDHT11_H
 #define _TERRDHT11_H

 // DHTesp library from https://desire.giesecke.tk/index.php/2018/01/30/esp32-dht11/
#include <DHTesp.h>

namespace TerrDHT11 {
  extern DHTesp _dht;
  extern unsigned int _dhtPin;
  extern const char *_lastStatus;
  extern TempAndHumidity _lastValues;

  void init (unsigned int);
  void update ();
  static float temp () {return _lastValues.temperature;};
  static float humidity () {return _lastValues.humidity;};
  static const char *lastStatus () {return _lastStatus;};
}

#endif // _TERRDHT11_H
