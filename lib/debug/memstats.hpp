#ifndef _H_MEMSTATS
#define _H_MEMSTATS
#ifdef ARDUINO_AVR_UNO
  #define MEM_TOTAL 2048 // Arduino Uno (2KB SRAM)
#elif defined(ARDUINO_AVR_MEGA2560)
  #define MEM_TOTAL 8192 // Arduino Mega (8KB SRAM)
#elif defined(ARDUINO_AVR_NANO)
  #define MEM_TOTAL 2048 // Arduino Nano (2KB SRAM)
#elif defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_PROMICRO16) 
  #define MEM_TOTAL 2560 // Arduino Leonardo/Micro (2.5KB SRAM, ATmega32U4)
#else
  #pragma message "Unknown board, please define MEM_TOTAL for your board."
  #define MEM_TOTAL 2048 // Default to 2KB if board is not specifically defined
#endif

int memfree();
#endif
