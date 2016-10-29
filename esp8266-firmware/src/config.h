#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <alarm.h>

bool loadWifiSettings(String *ssid, String *pass);
bool saveWifiSettings(String *ssid, String *pass);

void loadAlarms(alarm *alarms);
void saveAlarms(alarm *alarms);

static void extractAlarmTimeFromString(String *string, alarm *alarm);
static void appendAlarmTimeToString(String *string, alarm *alarm);
#endif
