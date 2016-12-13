#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include <Hash.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>

#include "webserver.h"
#include "alarm.h"
#include "config.h"
#include "light.h"

AsyncWebServer server(80);

String days[] = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday" };

static void lightOn_CB(AsyncWebServerRequest *request) {
  lightOn();
  request->send(200);
}

static void lightOff_CB(AsyncWebServerRequest *request) {
  lightOff();
  request->send(200);
}

static void setAlarms(AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
  StaticJsonBuffer<500> jsonBuffer;
  JsonObject &object = jsonBuffer.parseObject((char *) data);

  for (int i = 0; i < 7; i++) {
    JsonObject &timeObject = object[days[i]];
    String time = timeObject["time"];
    alarms[i].hour = time.substring(0,2).toInt();
    alarms[i].minute = time.substring(3,5).toInt();
    alarms[i].enabled = timeObject["enabled"];
  }

  saveAlarms(alarms);
  request->send(200);
}

static void getAlarms(AsyncWebServerRequest *request) {
  AsyncResponseStream *response = request->beginResponseStream("text/json");
  DynamicJsonBuffer jsonBuffer;
  JsonObject &root = jsonBuffer.createObject();

  for (int i = 0; i < 7; i++) {
    JsonObject& nestedObject = root.createNestedObject(days[i]);
    String time = "";
    if (alarms[i].hour < 10) {
      time += "0";
    }
    time += String(alarms[i].hour);

    time += ":";

    if (alarms[i].minute < 10) {
      time += "0";
    }
    time += String(alarms[i].minute);

    nestedObject["time"] = time;
    nestedObject["enabled"] = alarms[i].enabled;
  }

  root.printTo(*response);
  request->send(response);

  request->send(200);
}

static void sendOk(AsyncWebServerRequest *request) {
  //request->send(200);

}

void webServerInit() {
  // Pages
  server.serveStatic("/", SPIFFS, "/www/").setDefaultFile("index.html");
  //server.serveStatic("/alarm.html", SPIFFS, "www/alarm.html");
  //server.serveStatic("/light.html", SPIFFS, "www/light.html");
  //server.serveStatic("/settings.html", SPIFFS, "www/settings.html");
  //server.serveStatic("/", SPIFFS, "www/index.html");

  // LIGHT API
  server.on("/api/light/on", HTTP_POST, lightOn_CB);
  server.on("/api/light/off", HTTP_POST, lightOff_CB);

  // ALARM API
  server.on("/api/alarms", HTTP_GET, getAlarms);
  server.on("/api/alarms", HTTP_POST, sendOk).onBody(setAlarms);
  server.begin();
}
