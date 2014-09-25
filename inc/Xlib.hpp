#ifndef _XLIB_HPP_
#define _XLIB_HPP_

#include <cstring>
#include <cassert>
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <gtk/gtk.h>

#include "inc/Gdk.hpp"
#include "inc/Logger.hpp"
#include "inc/Config.hpp"

using namespace std;

const unsigned int kModifiersMasks[] = {
  0,                                // No additional modifier.
  Mod2Mask,                         // Num lock
  LockMask,                         // Caps lock
  Mod5Mask,                         // Scroll lock
  Mod2Mask | LockMask,
  Mod2Mask | Mod5Mask,
  LockMask | Mod5Mask,
  Mod2Mask | LockMask | Mod5Mask
};

class Xlib {
 private:
  Display *display_;
  Gdk *gdk_;

 public:
  Xlib(int argc, char *argv[]) {
    display_ = XOpenDisplay(":0.0");
    gdk_ = new Gdk(argc, argv);
  };

  ~Xlib() {
    XCloseDisplay(display_);
    delete gdk_;
  }

  Display *GetDisplay() {
    return display_;
  }

  Window GetRootWindow() {
    assert(display_ != NULL);

    return XDefaultRootWindow(display_);
  }

  void RegisterHotkey() {
    assert(display_ != NULL);

    int key_left = XKeysymToKeycode(display_, XK_Left);
    int key_right = XKeysymToKeycode(display_, XK_Right);
    int key_up = XKeysymToKeycode(display_, XK_Up);
    int key_down = XKeysymToKeycode(display_, XK_Down);
    int key_interrupt = GetKeyQuit();
    unsigned int modifiers = GetKeyModifiers();
    Bool owner_events = False;
    int pointer_mode = GrabModeAsync;
    int keyboard_mode = GrabModeAsync;
    XEvent x_event;
    Window root_window = GetRootWindow();

    for (int i = 0; i < sizeof(kModifiersMasks) / sizeof(*kModifiersMasks); i++) {
      XGrabKey(display_, key_left, modifiers | kModifiersMasks[i], root_window, owner_events, pointer_mode, keyboard_mode);
      XGrabKey(display_, key_right, modifiers | kModifiersMasks[i], root_window, owner_events, pointer_mode, keyboard_mode);
      XGrabKey(display_, key_up, modifiers | kModifiersMasks[i], root_window, owner_events, pointer_mode, keyboard_mode);
      XGrabKey(display_, key_down, modifiers | kModifiersMasks[i], root_window, owner_events, pointer_mode, keyboard_mode);
      XGrabKey(display_, key_interrupt, modifiers | kModifiersMasks[i], root_window, owner_events, pointer_mode, keyboard_mode);
    }

    XSelectInput(display_, root_window, KeyPressMask);

    bool interrupted = false;
    while (!interrupted) {
      XNextEvent(display_, &x_event);
      switch (x_event.type) {
        case KeyPress:
          // XUngrabKey(display, key, modifiers, GetRootWindow());
          if (x_event.xkey.keycode == key_left) {
            Logger::getInstance().log(LOG_NOTICE, "Meta-Left pressed!");
            gdk_->MoveToLeft();
          } else if (x_event.xkey.keycode == key_right) {
            Logger::getInstance().log(LOG_NOTICE, "Meta-Right pressed!");
            gdk_->MoveToRight();
          } else if (x_event.xkey.keycode == key_up) {
            Logger::getInstance().log(LOG_NOTICE, "Meta-Up pressed!");
            gdk_->Maximize();
          } else if (x_event.xkey.keycode == key_down) {
            Logger::getInstance().log(LOG_NOTICE, "Meta-Down pressed!");
            gdk_->Minimize();
          } else if (x_event.xkey.keycode == key_interrupt) {
            Logger::getInstance().log(LOG_NOTICE, "Meta-C pressed! Quit.");
            interrupted = true;
          }
          break;
        default:
          break;
      }
    }

    for (int i = 0; i < sizeof(kModifiersMasks) / sizeof(*kModifiersMasks); i++) {
      XUngrabKey(display_, key_left, modifiers | kModifiersMasks[i], root_window);
      XUngrabKey(display_, key_right, modifiers | kModifiersMasks[i], root_window);
      XUngrabKey(display_, key_up, modifiers | kModifiersMasks[i], root_window);
      XUngrabKey(display_, key_down, modifiers | kModifiersMasks[i], root_window);
      XUngrabKey(display_, key_interrupt, modifiers | kModifiersMasks[i], root_window);
    }

    gtk_main_quit();
  }

  static void SendQuitKeyEvent() {
    Display *display = XOpenDisplay(":0.0");
    Window window = XDefaultRootWindow(display);

    XEvent x_event;
    x_event.xkey.type = KeyPress;
    x_event.xkey.keycode = GetKeyQuit();
    x_event.xkey.state = GetKeyModifiers();

    XSendEvent(display, window, True, KeyPressMask, &x_event);
    XFlush(display);
    XCloseDisplay(display);
  }

  static int GetKeyQuit() {
    Display *display = XOpenDisplay(":0.0");
    int key = XKeysymToKeycode(display, XK_C);
    XCloseDisplay(display);
    return key;
  }

  static int GetKeyModifiers() {
    return Mod4Mask;
  }
};

#endif