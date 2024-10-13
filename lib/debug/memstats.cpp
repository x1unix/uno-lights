#include <memstats.hpp>

extern int __heap_start, *__brkval;
int memfree() {
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
