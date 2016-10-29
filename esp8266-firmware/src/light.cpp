#include <Arduino.h>

#include "light.h"

#define PWM_PIN 5

bool fading = false;

void initLight() {
  pinMode(PWM_PIN, OUTPUT);
}

void lightOff() {
  fading = false;
  analogWrite(PWM_PIN, 0);
}

void lightOn() {
  fading = true;
  int i = 0;
  while (fading && i < PWMRANGE) {
    analogWrite(PWM_PIN, i);
    i++;
    delay(5);
  }
}

void startAlarm() {

}
