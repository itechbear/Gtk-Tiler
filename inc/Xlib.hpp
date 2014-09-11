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
    int key_up = XKeysymToKeycode(display, XK_Up);
    int key_down = XKeysymToKeycode(display, XK_Down);
    int key_interrupt = XKeysymToKeycode(display, XK_C);
    unsigned int modifiers = ShiftMask | Mod1Mask;
    Bool owner_events = False;
    int pointer_mode = GrabModeAsync;
    int keyboard_mode = GrabModeAsync;
    XEvent x_event;
    Window root_window = GetRootWindow();

    XGrabKey(display, key_left, modifiers, root_window, owner_events, pointer_mode, keyboard_mode);
    XGrabKey(display, key_right, modifiers, root_window, owner_events, pointer_mode, keyboard_mode);
    XGrabKey(display, key_up, modifiers, root_window, owner_events, pointer_mode, keyboard_mode);
    XGrabKey(display, key_down, modifiers, root_window, owner_events, pointer_mode, keyboard_mode);
    XGrabKey(display, key_interrupt, modifiers, root_window, owner_events, pointer_mode, keyboard_mode);

    XSelectInput(display, root_window, KeyPressMask);

    bool interrupted = false;
    while (!interrupted) {
      XNextEvent(display, &x_event);
      switch (x_event.type) {
        case KeyPress:
          // XUngrabKey(display, key, modifiers, GetRootWindow());
          if (x_event.xkey.keycode == key_left) {
            Logger::getInstance().log(LOG_NOTICE, "Alt-Left pressed!");
            gdk.MoveToLeft();
            gdk.MoveToLeft();
          } else if (x_event.xkey.keycode == key_right) {
            Logger::getInstance().log(LOG_NOTICE, "Alt-Right pressed!");
            gdk.MoveToRight();
            gdk.MoveToRight();
          } else if (x_event.xkey.keycode == key_up) {
            Logger::getInstance().log(LOG_NOTICE, "Alt-Up pressed!");
            gdk.MoveToUp();
            gdk.MoveToUp();
          } else if (x_event.xkey.keycode == key_down) {
            Logger::getInstance().log(LOG_NOTICE, "Alt-Down pressed!");
            gdk.MoveToDown();
            gdk.MoveToDown();
          } else if (x_event.xkey.keycode == key_interrupt) {
            Logger::getInstance().log(LOG_NOTICE, "Alt-C pressed! Quit.");
            interrupted = true;
          }
          break;
        default:
          break;
      }
    }

    XUngrabKey(display, key_left, modifiers, root_window);
    XUngrabKey(display, key_right, modifiers, root_window);
    XUngrabKey(display, key_up, modifiers, root_window);
    XUngrabKey(display, key_down, modifiers, root_window);
    XUngrabKey(display, key_interrupt, modifiers, root_window);
  }
};

#endif