/* 
 * Copyright (c) 2017 Christophe Rubeck.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU Lesser General Public License as   
 * published by the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * Lesser General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <PgmSpace.h>
#include <ArduinoJson.h>

#include "BlinkLed.h"
#include "LedStrip.h"

// Static web page elements in flash memory
#include "ledstripCSS.h"
#include "indexHTML.h"
#include "ledstripJS.h"
#include "faviconICO.h"

// Web service setup
const char* ssid = "your_ssid";
const char* password = "your_password";
const char* myHostname = "LedStrip";
const char port = 80;
const char* type = "http";
const char* proto = "tcp";

// Init blinking led
BlinkLed bl = BlinkLed(LED_BUILTIN,1000);

// Init ledstrip, args are led output pins
LedStrip ledstrip(14,12,13,15);

// Init webserver on port 80
ESP8266WebServer server(port);

void setup() {

  // Init serial
  Serial.begin(115200);
  delay(10);

  // Init blinking led
  bl.setup();

  // Start Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Serial report
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /* 
   *  MDNS advertissement
   */
  while (!MDNS.begin(myHostname)) {
    delay(500);
  }
  MDNS.addService(type, proto, port);
  MDNS.addServiceTxt(type, proto, "vendor", "Christux");
  MDNS.addServiceTxt(type, proto, "model", "LedStrip");
  MDNS.addServiceTxt(type, proto, "version", "1");
  MDNS.addServiceTxt(type, proto, "serial", "PROTO01");
  MDNS.addServiceTxt(type, proto, "firmware_build_date", __DATE__ " " __TIME__);
  MDNS.addServiceTxt(type, proto, "mac_adress", WiFi.macAddress());

  Serial.println("");
  Serial.println("MDNS started");

  /* 
   *  Config server routes
   */
   // Main page
  server.on("/", [](){
    Serial.println("Send index.html");
    server.send_P(200, "text/html", INDEX_HTML);
  });

  server.on("/css/ledStrip.css", [](){
    Serial.println("Send /css/ledStrip.css");
    server.send_P(200, "text/css", CSS);
  });

  server.on("/js/ledStrip.js", [](){
    Serial.println("Send /js/ledStrip.js");
    server.send_P(200, "text/script", JS);
  });

  server.on("/favicon.ico", [](){
    Serial.println("Send /favicon.ico");
    server.send_P(200, "image/x-icon", FAVICON, sizeof(FAVICON));
  });

  // Web api
  server.on("/api", HTTP_GET, getLeds);
  server.on("/api", HTTP_POST, setLeds);

  // Error 404
  server.onNotFound(handleNotFound);

  // Starts web server
  server.begin();

  Serial.println("");
  Serial.println("Server started");

  // Init ledstrip
  ledstrip.setup();
}

void loop() {

  MDNS.update();
  server.handleClient();
  bl.update();
}
