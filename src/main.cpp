#include <Arduino.h>
#include <timeouts.hpp>
#include <foundation.hpp>
#include <memstats.hpp>
#include <logger.hpp>

#define LED PIN3
#define MAX_INTENCITY 128
#define INTENCITY_STEP 4

auto timer = timeouts::Ticker(2);

void memstats() {
  int freeMem = memfree();
  int usedMem = MEM_TOTAL - freeMem;
  float percentageUsed = (float(usedMem) / float(MEM_TOTAL)) * 100;
  logger::println("Memory: total=", MEM_TOTAL, " free=", freeMem, " used=", usedMem, " ", percentageUsed, "%");
}

bool updateLed();

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);

  timer.setTimeout(updateLed, 50);
  timer.setTimeout([]() {
    Serial.println("Hello World");
    return false;
  }, 1000);
}

volatile int intencity = 0;
volatile bool increase = true;
volatile int blinkCount = 0;

bool updateLed() {
  analogWrite(LED, intencity);

  if (blinkCount == 1) {
    blinkCount = 0;
    timer.setTimeout([]() {
      memstats();
      timer.setTimeout(updateLed, 50);
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
    memstats();
    blinkCount++;
  }

  return true;
}

void loop() {
  timer.tick();
}
