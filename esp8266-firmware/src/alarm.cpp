#include <Arduino.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <Ticker.h>

#include "alarm.h"
#include "config.h"
#include "light.h"

alarm alarms[7];
Ticker checker;
WiFiUDP ntpUDP;


bool started = false;

void initAlarm() {
  loadAlarms(alarms);
  checker.attach(5, checkAlarm);
  NTP.begin("pool.ntp.org", 1, true);
  NTP.setInterval(63);
  delay(5000);
  bool dayLight = NTP.isSummerTimePeriod(now());
  Serial.println(dayLight);
}

static void checkAlarm() {
  uint8_t day = weekday() - 1;
  if (alarms[day].hour == hour() && alarms[day].minute == minute()) {
    Serial.println("Alarm time reached!");
    lightOn();
  }
}
