/* TerrDHT11.h
 * Interface to the DHT11 I'm using for the terrarium.
 */

 #ifndef _TERRDHT11_H
 #define _TERRDHT11_H

 // DHTesp library from https://desire.giesecke.tk/index.php/2018/01/30/esp32-dht11/
#include <DHTesp.h>

namespace TerrDHT11 {
  extern DHTesp dht;
  extern char *lastStatus;
  extern TempAndHumidity lastValues;
}

#endif // _TERRDHT11_H
