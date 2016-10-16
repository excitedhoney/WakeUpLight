#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "webserver.h"

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  pinMode(5, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin("HuizeSpiderman", "Noorderhagen46");

  MDNS.begin("esp8266");

  SPIFFS.begin();


  webServerInit();
}

void loop() {

}
