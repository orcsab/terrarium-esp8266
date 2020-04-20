/* TerrDHT11.cpp
 * Terrarium wrapper to the DHT11.
 */

 #include <DHTesp.h>

 #include "TerrDHT11.h"

 DHTesp TerrDHT11::dht;
 char *TerrDHT11::lastStatus;
 TempAndHumidity TerrDHT11::lastValues {0,0};
