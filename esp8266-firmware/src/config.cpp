#include <ArduinoJson.h>
#include "FS.h"

#include "config.h"

//void loadSettings() {
//  FILE config_file = SPIFFS.open("/config.json", "r");
//
//  if (!config_file) {
//    Serial.println("Failed to open config file");
//    return;
//  }
//
//  // Allocate a buffer for the file contents
//  std::unique_ptr<char[]> buf(new char[size]);
//  config_file.readBytes(buf.get(), size);
//
//  StaticJsonBuffer<200> jsonBuffer;
//  JsonObject& json = jsonBuffer.parseObject(buf.get());
//
//  if (!json.success()) {
//    Serial.println("Failed to parse config file");
//    return;
//  }
//
//  const char* password = json["PSK"];
//  const char* ssid = json["SSID"];
//
//  Serial.println(ssid);
//}
