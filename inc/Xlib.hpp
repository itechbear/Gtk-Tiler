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

  Window GetActiveWindow() {
    assert(display != NULL);

    Window window;
    int focus;
    XGetInputFocus(display, &window, &focus);

    return window;
  }

  Window GetRootWindow() {
    assert(display != NULL);

    return XDefaultRootWindow(display);
  }

  char *GetTitleOfWindow(Window window) {
    assert(display != NULL);

    Atom atom = XInternAtom(display, "WM_NAME", False), type;
    int form;
    unsigned long remain, len;
    unsigned char *list;


    if (XGetWindowProperty(display, window, atom, 0, 1024, False, AnyPropertyType, &type, &form, &len, &remain, &list) != Success) {
      return NULL;
    }

    return (char *) list;
  }

  Screen *GetScreen() {
    assert(display != NULL);

    return DefaultScreenOfDisplay(display);
  }

  XWindowAttributes GetAttributesOfWindow(Window window) {
    assert(display != NULL);

    XWindowAttributes xWindowAttributes;
    Status status = XGetWindowAttributes(display, window, &xWindowAttributes);
    assert(status != False);

    return xWindowAttributes;
  }

  int GetBorderWidthOfWindow(Window window) {
    assert(display != NULL);

    XWindowAttributes xWindowAttributes = GetAttributesOfWindow(window);

    return xWindowAttributes.border_width;
  }

  int MaximizeWindow(Window window) {
    assert(display != NULL);

    XEvent xEvent;

    Atom wm_state  =  XInternAtom(display, "_NET_WM_STATE", False);
    Atom horizontal =  XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    Atom vertical =  XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);
    // Atom sticky = XInternAtom(display, "_NET_WM_STATE_STICKY", False);
    Atom fullScreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

    memset(&xEvent, 0, sizeof(xEvent));
    xEvent.type = ClientMessage;
    xEvent.xclient.window = window;
    xEvent.xclient.message_type = wm_state;
    xEvent.xclient.format = 32;
    xEvent.xclient.data.l[0] = 1;
    xEvent.xclient.data.l[1] = fullScreen;
    xEvent.xclient.data.l[2] = 0;
    // xEvent.xclient.data.l[3] = sticky;

    return XSendEvent(display, window, False, SubstructureNotifyMask, &xEvent);
  }

  int RefreshWindow(Window window) {
    assert(display != NULL);

    XEvent xEvent;

    memset(&xEvent, 0, sizeof(xEvent));
    xEvent.type = Expose;
    xEvent.xexpose.window = window;

    return XSendEvent(display, window, False, ExposureMask, &xEvent);
  }

  int ResizeWindow(Window window, int width, int height) {
    assert(display != NULL);

    return XResizeWindow(display, window, width, height);
  }

  int MoveWindow(Window window, int x, int y) {
    assert(display != NULL);

    return XMoveWindow(display, window, x, y);
  }

  int ResizeAndMoveLeft(Window window) {
    assert(display != NULL);

    Screen *screen = GetScreen();
    int width = screen->width;
    int height = screen->height;
    int border = GetBorderWidthOfWindow(window);

    ResizeWindow(window, width/2 - 2 * border, height - 2 * border);
    MoveWindow(window, 0, 0);
  }

  int ResizeAndMoveRight(Window window) {
    assert(display != NULL);

    Screen *screen = GetScreen();
    int width = screen->width;
    int height = screen->height;
    int border = GetBorderWidthOfWindow(window);

    ResizeWindow(window, width/2 - 2 * border, height - 2 * border);
    MoveWindow(window, width/2, 0);
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