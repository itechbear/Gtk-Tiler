#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <syslog.h>

#include <string>

using namespace std;

class Logger {
 private:
  Logger() {
    openlog("X-Tiler", LOG_PID, LOG_DAEMON);
  };

 public:
  ~Logger() {
    closelog();
  };

  static Logger &getInstance() {
    static Logger instance;
    return instance;
  }

  void log(int level, string message) {
    syslog(level, message.c_str());
  }
};

#endif