/* TerrPhoto.h
 * Interface to the photo sensor at the Terrarium.
 */

 #ifndef _TERRPHOTO_H
 #define _TERRPHOTO_H

namespace TerrPhoto {
  void init (unsigned int, unsigned int);
  const char* desc();
  void update();

  // LED pin to show status
  extern unsigned int _ledPin;

  // Last pResistor value
  extern unsigned int _photoValue;

  // pin on the NodeMCU to which the photoresistor is connected.
  extern unsigned int _pResistorPin;
}

#endif // _TERRPHOTO_H
