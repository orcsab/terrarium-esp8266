/* TerrServer.h
 * Wraps ESP8266WebServer library with functionality unique to my terrarium
 * controller.
 */

#ifndef _TERRSERVER_H
#define _TERRSERVER_H

#include <ESP8266WebServer.h>

namespace TerrServer {
  void init (const char *, const char *, int port, int statusPin);
  void handleClient ();

  // Webserver port number
  extern int _port;

  // LED status pin to show activity on the web server. Optionally defined.
  extern int _statusPin;

  // The ESP8266WebServer library object.
  extern ESP8266WebServer *_server;

  void _handleRoot();
  void _handleNotFound();
};

#endif // _TERRSERVER_H
