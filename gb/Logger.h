#ifndef __LOGGER_H_
#define __LOGGER_H_ 1

  static void Logger_debug(const char* str) { printf("(ii) %s\n", str); }
  static void Logger_TMPDBUG(const char* str) { printf("(?i) %s\n", str); }
  
#endif