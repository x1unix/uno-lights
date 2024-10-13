#include <Arduino.h>
#include <Ticker.hpp>

template class foundation::Vec<timeouts::Ticker::Timer>;
template class foundation::Option<timeouts::Ticker::Timer>;

namespace timeouts {
Ticker::Ticker(int poolSize)
  : timers(foundation::Vec<Ticker::Timer>(poolSize)), freeSlots(foundation::Vec<int>(poolSize)) {
}

int Ticker::setTimeout(TimerCallback callback, Duration delay) {
  auto now = millis();
  int i = addTimer(Timer{
    .callback = callback,
    .lastExecutedAt = now,
    .interval = delay,
  });

  return i;
}

int Ticker::addTimer(Timer t) {
  // TODO: sort timers by interval.
  auto slot = freeSlots.pop();
  if (slot.is_none()) {
    return timers.push(t);
  }

  int i = slot.unwrap();
  timers[i] = t;
  return i;
}

void Ticker::disposeTimer(int i) {
  // TODO: shrink buffer if freeSlots is too big.
  if (timers.length() <= i) {
    return;
  }

  Ticker::Timer& timer = timers[i];
  if (isTimerDisposed(timer)) {
    return;
  }

  timer.callback = nullptr;
  freeSlots.push(i);
}

void Ticker::clearTimeout(int id) {
  disposeTimer(id);
}

bool Ticker::isTimerDisposed(Timer& t) {
  return t.callback == nullptr;
}

void Ticker::tick() {
  Duration now;
  bool isRepeated = false;
  for (int i = 0; i < timers.length(); i++) {
    Timer& timer = timers[i];
    if (isTimerDisposed(timer)) {
      continue;
    }

    now = millis();
    auto delta = now - timer.lastExecutedAt;
    if (delta < timer.interval) {
      continue;
    }

    isRepeated = timer.callback();
    if (!isRepeated) {
      disposeTimer(i);
      continue;
    }

    timer.lastExecutedAt = millis();
  }
}

};
