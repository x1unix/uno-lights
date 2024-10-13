#include <Arduino.h>

namespace logger {
template<typename T>
void println(T last) {
  Serial.println(last);
}

template<typename T, typename... Args>
void println(T first, Args... args) {
  Serial.print(first);
  Serial.print(" ");
  println(args...);
}
}
