/* TerrPhoto.cpp
 * Interface to the photocell in the terrarium.
 */

#include <arduino.h>

#include "TerrPhoto.h"

unsigned int TerrPhoto::_ledPin;
unsigned int TerrPhoto::_pResistorPin;
unsigned int TerrPhoto::_photoValue;

/* init
 * set the pin to which the photoresistor is connected
 * pResPin: the analog input pin to which the photocell is attached
 * ledPin: a pin to which an LED is attached to write status.
 */
void TerrPhoto::init (unsigned int pResPin, unsigned int ledPin)
{
  _pResistorPin = pResPin;
  _ledPin = ledPin;

  pinMode(_pResistorPin, INPUT);
  pinMode(_ledPin, OUTPUT);
}
/* desc
 * Return the status from the last attempt to read the DHT11.
 */
const char *TerrPhoto::desc() {
  if (_photoValue > 800)
    return "dark";
  else if (_photoValue > 600)
    return "dim";
  else if (_photoValue > 400)
    return "lit";
  else
    return "bright";
}

/* update
 * updates the photo resistor value to _photoValue
 */
void TerrPhoto::update () {
  _photoValue = analogRead(_pResistorPin);

  // LED glows when the room is dark.
  if (std::string(desc()) == "dark")
    digitalWrite(_ledPin, HIGH);
  else
    digitalWrite(_ledPin, LOW);

}
