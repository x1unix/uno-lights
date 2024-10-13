#include <Arduino.h>
#include <timeouts.hpp>
#include <foundation.hpp>

#define LED PIN3
#define MAX_INTENCITY 128
#define INTENCITY_STEP 1

auto timer = timeouts::Ticker(2);

bool updateLed();

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  timer.setTimeout(updateLed, 10);
  timer.setTimeout([]() {
    Serial.println("Hello World");
    return false;
  }, 1000);
}

volatile int intencity = 0;
volatile bool increase = true;
volatile int blinkCount = 0;

// See: https://alexgyver.ru/lessons/led-crt/
uint8_t crt2_8(uint8_t val) {
  return ((uint32_t)(val + 1) * val) >> 8;
}

bool updateLed() {
  analogWrite(LED, crt2_8(intencity));

  if (blinkCount == 1) {
    blinkCount = 0;
    timer.setTimeout([]() {
      timer.setTimeout(updateLed, 10);
      return false;
    }, 3000);
    return false;
  }

  if (increase) {
    intencity += INTENCITY_STEP;
    increase = intencity < MAX_INTENCITY;
    return true;
  }

  intencity -= INTENCITY_STEP;
  increase = intencity <= 0;
  if (increase) {
    blinkCount++;
  }

  return true;
}

void loop() {
  timer.tick();
}
