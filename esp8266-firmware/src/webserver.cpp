#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Hash.h>

#include "webserver.h"

AsyncWebServer server(80);

static void lightOn(AsyncWebServerRequest *request) {
  digitalWrite(5, HIGH);
  request->send(200);
}

static void lightOff(AsyncWebServerRequest *request) {
  digitalWrite(5, LOW);
  request->send(200);
}

static void setAlarms(AsyncWebServerRequest *request) {
  digitalWrite(5, LOW);
  request->send(200);
}

static void getAlarms(AsyncWebServerRequest *request) {
  digitalWrite(5, LOW);
  request->send(200);
}

void webServerInit() {
  // Pages
  server.serveStatic("/alarm.html", SPIFFS, "www/alarm.html");
  server.serveStatic("/light.html", SPIFFS, "www/light.html");
  server.serveStatic("/settings.html", SPIFFS, "www/settings.html");
  server.serveStatic("/", SPIFFS, "www/index.html").setDefaultFile("www/index.html");

  // LIGHT API
  server.on("/api/light/on", HTTP_POST, lightOn);
  server.on("/api/light/off", HTTP_POST, lightOff);

  // ALARM API
  server.on("/api/alarm", HTTP_POST, )
  server.begin();
}
