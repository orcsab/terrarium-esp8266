/* TerrServer.cpp
 * Wrapper for ESP8266WebServer for my terrarium.
 */

 #include <ESP8266WebServer.h>
 #include <WifiClient.h>
 #include <ESP8266mDNS.h>

#include "TerrServer.h"
#include "TerrDHT11.h"
#include "TerrLight.h"

int TerrServer::_port;
int TerrServer::_statusPin;
ESP8266WebServer *TerrServer::_server;

/* Constructor.
 * Initialize the web server and setup the handlers I want specifically for the
 * terrarium.
 */
void TerrServer::init (const char *ssid, const char *pass, int port, int statusPin=-1) {
  _port = port;
  _statusPin = statusPin;

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

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  _server = new ESP8266WebServer(port);
  _server->on("/", _handleRoot);
  _server->onNotFound(_handleNotFound);
  _server->begin();

  Serial.println("HTTP server started");
}

/* handleClient
 * Calls the ESP8266WebServer function of the same name.
 */
void TerrServer::handleClient () {
  _server->handleClient();
}

/* Handler for calls to HTML root.
 */
void TerrServer::_handleRoot (void) {
  if (_statusPin >= 0)
    digitalWrite(_statusPin, HIGH);

  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;

  snprintf(temp, 400,
    "<html>\
    <head>\
      <meta http-equiv='refresh' content='5'/>\
      <title>ESP8266 Demo</title>\
      <style>\
        body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
      </style>\
    </head>\
    <body>\
      <h1>Hello from ESP8266!</h1>\
      <p>Uptime: %02d:%02d:%02d</p>\
      <p>Light: %s, Temperature: %2.1f, Humidity: %2.1f, Status: %s</p>\
      <!-- <img src=\"/test.svg\" />  --> \
    </body>\
    </html>",
    hr, min % 60, sec % 60, TerrLight::lightDesc(),
    TerrDHT11::lastValues.temperature, TerrDHT11::lastValues.humidity, TerrDHT11::dht.getStatusString()
  );
  _server->send(200, "text/html", temp);

  if (_statusPin >= 0)
    digitalWrite(_statusPin, LOW);
}

/* _handleNotFound
 * Called by the ESP8266WebServer when a request is made to a URL that is not
 * defined.
 */
void TerrServer::_handleNotFound () {
  if (_statusPin >= 0)
    digitalWrite(_statusPin, HIGH);

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += _server->uri();
  message += "\nMethod: ";
  message += (_server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += _server->args();
  message += "\n";

  for (uint8_t i = 0; i < _server->args(); i++) {
    message += " " + _server->argName(i) + ": " + _server->arg(i) + "\n";
  }

  _server->send(404, "text/plain", message);

  if (_statusPin >= 0)
    digitalWrite(_statusPin, LOW);
}
