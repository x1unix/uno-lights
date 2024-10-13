#include <Vec.hpp>
#include <Option.hpp>

#ifndef _H_EVENTLOOP
#define _H_EVENTLOOP


namespace timeouts {

typedef unsigned long Duration;

typedef bool (*TimerCallback)();

/**
 * Ticker manages and executes scheduled timeouts and intervals.
 */
class Ticker {
public:
  /**
   * Constructs a new ticker with a specified queue capacity.
   * 
   * Ticker grows queue size if number of scheduled timers is bigger that initial pool size.
   */
  Ticker(int poolSize);

  /**
   * Sets a timer which executes a function or specified piece of code once the timer expires.
   * 
   * Timeout is repeated if passed callback returns true.
   * 
   * This method returns an interval ID which identifies the interval, so you can remove it later by calling clearTimeout().
   */
  int setTimeout(TimerCallback callback, Duration delay);

  /**
   * Cancels a timeout previously established by calling setTimeout().
   */
  void clearTimeout(int id);

  void tick();

private:
  struct Timer {
    TimerCallback callback;
    Duration lastExecutedAt;
    Duration interval;
  };

  foundation::Vec<Timer> timers;
  foundation::Vec<int> freeSlots;
  int addTimer(Timer t);
  void disposeTimer(int i);

  static bool isTimerDisposed(Timer& t);
};
}
#endif
