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

#include <NeoPixelBus.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ChristuxUtils.h>
#include <ChristuxAnimation.h>
#include <ArduinoJson.h>

#include "eeprom.h"
#include "ledstripHTML.h"
#include "ledstripJS.h"
#include "ledstripCSS.h"
#include "faviconICO.h"

// Defines constants
const char* ssid = "your_ssid";
const char* password = "your_password";
const char* myHostname = "LedStrip";
const char port = 80;
const char* type = "http";
const char* proto = "tcp";

// Blinking build-in led
BlinkLed bl(LED_BUILTIN,1000);

// RGB strip
int PixelCount=30;

NeoPixelAdapter<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

Animator animator;

Rainbow rainbow(PixelCount, &strip);
Sunrise sunrise(PixelCount, &strip, 30*60); // 30 minutes
UniColor unicolor(PixelCount, &strip);
Off off(PixelCount, &strip);
Flag flag(PixelCount, &strip);
Comet comet(PixelCount, &strip);
Theater theater(PixelCount, &strip);
KnightRider rider(PixelCount, &strip);
RainbowLamp lamp(PixelCount, &strip);
RainbowLampRandom randlamp(PixelCount, &strip);
Fire fire(PixelCount, &strip);
Breathing breath(PixelCount, &strip);

// Start webserver on port 80
ESP8266WebServer server(port);

// Read and write configuration from EEPROM
Config config;


void setup() {

  // Blinking led
  bl.setup();

  // Starts Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  while (!MDNS.begin(myHostname,WiFi.localIP(),30)) {
    delay(500);
  }
  MDNS.addService(type, proto, port);
  MDNS.addServiceTxt(type, proto, "vendor", "Christux");
  MDNS.addServiceTxt(type, proto, "model", "LedStrip01");
  MDNS.addServiceTxt(type, proto, "version", "1");
  MDNS.addServiceTxt(type, proto, "serial", "PROTO01");
  MDNS.addServiceTxt(type, proto, "firmware_build_date", __DATE__ " " __TIME__);
  MDNS.addServiceTxt(type, proto, "mac_adress", WiFi.macAddress());

  // HTTP server
  server.on("/", [](){
    server.send_P(200, "text/html", INDEX_HTML);
  });
  server.on("/index.html", [](){
    server.send_P(200, "text/html", INDEX_HTML);
  });
  server.on("/js/RGBledStrip.js",HTTP_GET, [](){
    server.send_P(200, "text/script", JS);
  });
  server.on("/css/RGBledStrip.css", HTTP_GET, [](){
    server.send_P(200, "text/css", CSS);
  });
  server.on("/favicon.ico",HTTP_GET, [](){
    server.send_P(200, "image/x-icon", FAVICON, sizeof(FAVICON));
  });
  server.on("/api", HTTP_GET, getConfig);
  server.on("/api", HTTP_POST, setConfig);
  server.on("/info", HTTP_GET, getInfo);
  server.onNotFound(handleNotFound);
  server.begin();
  
  // Starts NeoPixelBus
  strip.Begin();

  // Register animations in animator
  animator.add(&unicolor);
  animator.add(&lamp);
  animator.add(&randlamp);
  animator.add(&rainbow);
  animator.add(&comet);
  animator.add(&breath);
  animator.add(&fire);
  animator.add(&theater);
  animator.add(&rider);
  animator.add(&flag);
  animator.add(&sunrise);
  animator.add(&off);

  // Read config from EEPROM
  animator.setAnimation(config.readAnim());
  animator.setColor(config.readColor());

  // Enable OTA
  ArduinoOTA.setHostname(myHostname);
  ArduinoOTA.onStart([]() {
    strip.SetAllPixels(RgbColor(0,0,0));
    strip.Show();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    RgbColor color(64,0,0);
    for(int i=0, l=PixelCount*progress/total; i<l; i++)
    {
      strip.SetPixelColor(i,color);
    }
    strip.Show();
  });
  ArduinoOTA.onEnd([]() {
   strip.SetAllPixels(RgbColor(0,0,0));
   strip.Show();
  });
  ArduinoOTA.onError([](ota_error_t error) {
    ESP.restart();
  });
  ArduinoOTA.begin();
}

void loop() {

  bl.handle();
  ArduinoOTA.handle();
  MDNS.update();
  animator.handle();
  server.handleClient();
}

