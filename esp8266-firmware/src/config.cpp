
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <FS.h>
#include <ArduinoOTA.h>

#include "config.h"
#include "alarm.h"

void loadSettings() {

}

/**
 * Reads the wifi settings from wifi_conf.txt where the ssid
 * and password must be saved as ssid:password
 **/
bool loadWifiSettings(String *ssid, String *pass) {
  File wifiSettings = SPIFFS.open("/wifi_conf.txt", "r");
  if (!wifiSettings) {
    // TODO handle error
  }

  String content = wifiSettings.readString();
  wifiSettings.close();

  // Remove the line ending
  content.trim();

  // Get the position of the split character
  uint8_t split = content.indexOf(':');
  uint8_t length = content.length();

  // Extract the settings from the string
  *ssid = content.substring(0, split);
  *pass = content.substring(split + 1, length);

  Serial.println("Loaded wifi SSID: " + *ssid);
  Serial.println("Loaded wifi password" + *pass);
}

/**
 * Saves the wifi settings in wifi_conf.txt where the ssid
 * and password must be saved as ssid:password
 **/
bool saveWifiSettings(String *ssid, String *pass) {
  File wifiSettings = SPIFFS.open("/wifi_conf.txt", "w");

  wifiSettings.print(*ssid);
  wifiSettings.print(':');
  wifiSettings.println(*pass);

  wifiSettings.close();
}
/**
 * Loads the alarm times from alarm_conf.txt. The config file
 * must have all the alarms in one string on the first line in
 * the following format: monday=7:00;tuesday=18:00;.....
 **/
void loadAlarms(alarm *alarms) {
  // Open the alarms settings file and read the contents
  File alarmSettings = SPIFFS.open("/alarm_conf.txt", "r");
  String content = alarmSettings.readString();
  alarmSettings.close();

  uint8_t x = 0;
  for (int i = 0; i <= 6; i++) {
    uint8_t pos = content.indexOf(';', x);
    String substring = content.substring(x, pos);
    extractAlarmTimeFromString(&substring, &alarms[i]);
    x = pos + 1;
  }
}

void saveAlarms(alarm *alarms) {
  String content = "";
  for (int i = 0; i < 7; i++) {
    appendAlarmTimeToString(&content, &alarms[i]);
  }

  File alarmSettings = SPIFFS.open("/alarm_conf.txt", "w");
  alarmSettings.print(content);
  alarmSettings.close();
}

static void appendAlarmTimeToString(String *string, alarm *alarm) {
  *string += "&&";
  *string += "=";
  *string += String(alarm->hour);
  *string += ':';
  *string += String(alarm->minute);
  *string += ',';
  *string += String(alarm->enabled);
  *string += ';';
}

static void extractAlarmTimeFromString(String *string, alarm *alarm) {
  uint8_t splitter = string->indexOf('=');
  uint8_t splitter1 = string->indexOf(',');
  String substring = string->substring(splitter + 1, splitter1);

  splitter = substring.indexOf(':');
  String hour = substring.substring(0, splitter);
  String minute = substring.substring(splitter + 1);
  Serial.println(hour + " " + minute);

  alarm->hour = hour.toInt();
  alarm->minute = minute.toInt();

  char a = string->charAt(splitter1 + 1);
  if (a == '1'){
    alarm->enabled = true;
  }
  else {
    alarm->enabled = false;
  }
}
