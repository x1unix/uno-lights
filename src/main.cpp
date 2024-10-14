#include <Arduino.h>
#include <timeouts.hpp>
#include <foundation.hpp>

#define PIN9 9

const int8_t leds[] = {PIN9, PIN6, PIN5, PIN3};
const int8_t pinCount = uint8_t(sizeof(leds) / sizeof(int8_t));

auto timer = timeouts::Ticker(2);

bool updateLed();

typedef void (*PinCallback)(int8_t);
inline void pinForEach(PinCallback cb) {
  for (int8_t i = 0; i < pinCount; i++) {
    cb(leds[i]);
  }
}

void setup() {
  Serial.begin(9600);
  pinForEach([](int8_t pin) {
    pinMode(pin, OUTPUT);
  });

  timer.setTimeout(updateLed, 4);
  timer.setTimeout([]() {
    Serial.println("Hello World");
    return false;
  }, 1000);
}

// See: https://alexgyver.ru/lessons/led-crt/
uint8_t crt2_8(uint8_t val) {
  return ((uint32_t)(val + 1) * val) >> 8;
}

#define MAX_INTENCITY 128
#define INTENCITY_STEP 4

uint8_t ledValues[] = {0, 0, 0, 0};
int8_t currentPos = 0;
bool increase = true;

bool updateLed() {
  if (currentPos >= pinCount) {
    increase = !increase;
    currentPos = 0;
    return true;
  }

  auto pin = leds[currentPos];
  auto value = ledValues[currentPos];

  analogWrite(pin, crt2_8(value));
  if (increase) {
    if (value >= MAX_INTENCITY) {
      currentPos++;
    } else {
      ledValues[currentPos]++;
    }

    return true;
  }


  if (value <= 0) {
    currentPos++;
  } else {
    ledValues[currentPos]--;
  }

  return true;
}

void loop() {
  timer.tick();
}
