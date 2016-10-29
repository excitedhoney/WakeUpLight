#ifndef ALARM_H
#define ALARM_H

#include <ESP8266WiFi.h>

typedef struct {
  uint8_t hour;
  uint8_t minute;
  bool enabled;
} alarm;

extern alarm alarms[7];

void initAlarm();

static void checkAlarm();

static void syncTime();

#endif
