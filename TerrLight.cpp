/* TerrLight.cpp
 * Interface to the light measurement capabilities in the terrarium.
 */

#include "TerrLight.h"

/* lightDesc
 * Return the status from the last attempt to read the DHT11.
 */
const char *TerrLight::lightDesc() {
  return "OK";
}
