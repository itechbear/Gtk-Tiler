#ifndef _THREAD_HPP_
#define _THREAD_HPP_

#include "inc/Xlib.hpp"
#include "inc/Gdk.hpp"

class Thread {
 private:
  Xlib *xlib_;

 public:
  Thread(Xlib &xlib) {
    xlib_ = &xlib;
  }

  static void *Monitor(void *arg) {
    assert(arg != NULL);

    Xlib *xlib = (Xlib *) arg;

    xlib->RegisterHotkey();
  }

  int Start() {
    pthread_t pid;
    return pthread_create(&pid, NULL, &Thread::Monitor, xlib_);
  }
};

#endif // _THREAD_HPP_