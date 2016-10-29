#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <FS.h>

#include "webserver.h"
#include "config.h"
#include "alarm.h"

#define DEBUG

bool testWifi() {
  int c = 0;
  Serial.println("Waiting for Wifi to connect");
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) { return true; }
    delay(500);
    Serial.print(WiFi.status());
    c++;
  }
  Serial.println("");
  Serial.println("Connect timed out, opening AP");
  return false;
}

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);

  // Start the file system
  SPIFFS.begin();

  // Load the alarm and wifi settings from EEPROM
  String wifiSsid = "";
  String wifiPassword = "";
  loadWifiSettings(&wifiSsid, &wifiPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  initAlarm();
  webServerInit();
}


void loop() {

}
