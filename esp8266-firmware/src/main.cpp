#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "webserver.h"
#include "config.h"
#include "alarm.h"

#define DEBUG

void startNormalMode() {
  initAlarm();
  webServerInit();

  Serial.println("Starting MDNS");

  if (!MDNS.begin("ESP8266")) {
    Serial.println("Cannot setup MDNS!");
  }
  MDNS.addService("http", "tcp", 80);

  Serial.println(WiFi.localIP());
}

void startConfigMode() {
  WiFi.beginSmartConfig();

  // Wait for smart config
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    Serial.println(WiFi.smartConfigDone());
  }

  // If smartconfig done start normal mode.
  startNormalMode();
}


bool tryConnectWifi() {
  int retries = 0;

  WiFi.mode(WIFI_STA);
  Serial.print("Trying to connect to WiFi");

  while(WiFi.status() != WL_CONNECTED && retries < 20) {
    Serial.print(".");
    retries++;
    delay(1000);
  }

  return (WiFi.status() == WL_CONNECTED);
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  // Start the file system
  SPIFFS.begin();

  // Try to connect WiFi
  bool connected = tryConnectWifi();

  if (connected) {
    startNormalMode();
  }
  else {
    startConfigMode();
  }
}


void loop() {

}
