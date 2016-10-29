#include <Arduino.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
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

static void syncTime() {
  Serial.print("The time is: ");
  Serial.println(NTP.getTimeDateString());

  Serial.print("The date is: ");
  Serial.print(month(now()));
  Serial.print(":");
  Serial.println(day(now()));

  Serial.print("Todays alarm is set to: ");
  Serial.print(alarms[weekday(now())].hour);
  Serial.print(':');
  Serial.println(alarms[weekday(now())].minute);

  Serial.print("Today is a: ");
  Serial.println(weekday(now() + 172800));
}
