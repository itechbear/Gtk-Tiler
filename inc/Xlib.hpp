#ifndef _XLIB_HPP_
#define _XLIB_HPP_

#include <cstring>
#include <cassert>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "inc/Gdk.hpp"
#include "inc/Logger.hpp"

using namespace std;

class Xlib {
 private:
  Display *display;

 public:
  Xlib() {
    display = XOpenDisplay(":0.0");
  };

  ~Xlib() {
    XCloseDisplay(display);
  }

  Window GetRootWindow() {
    assert(display != NULL);

    return XDefaultRootWindow(display);
  }

  void RegisterHotkey(Gdk &gdk) {
    assert(display != NULL);

    int key_left = XKeysymToKeycode(display, XK_Left);
    int key_right = XKeysymToKeycode(display, XK_Right);
    int key_interrupt = XKeysymToKeycode(display, XK_C);
    unsigned int modifiers = Mod1Mask;
    Bool ownerEvents = False;
    int pointerMode = GrabModeAsync;
    int keyboardMode = GrabModeAsync;
    XEvent xEvent;

    XGrabKey(display, key_left, modifiers, GetRootWindow(), ownerEvents, pointerMode, keyboardMode);
    XGrabKey(display, key_right, modifiers, GetRootWindow(), ownerEvents, pointerMode, keyboardMode);
    XGrabKey(display, key_interrupt, modifiers, GetRootWindow(), ownerEvents, pointerMode, keyboardMode);

    XSelectInput(display, GetRootWindow(), KeyPressMask);

    bool interrupted = false;
    while (!interrupted) {
      XNextEvent(display, &xEvent);
      switch (xEvent.type) {
        case KeyPress:
          // XUngrabKey(display, key, modifiers, GetRootWindow());
          if (xEvent.xkey.keycode == key_left) {
            Logger::getInstance().log(LOG_NOTICE, "Alt-Left pressed!");
            gdk.MoveToLeft();
          } else if (xEvent.xkey.keycode == key_right) {
            Logger::getInstance().log(LOG_NOTICE, "Alt-Right pressed!");
            gdk.MoveToRight();
          } else if (xEvent.xkey.keycode == key_interrupt) {
            cout << "Alt-C pressed! Quit." << endl;
            Logger::getInstance().log(LOG_NOTICE, "Alt-C pressed! Quit.");
            interrupted = true;
          }
          break;
        default:
          break;
      }
    }
  }
};

#endif