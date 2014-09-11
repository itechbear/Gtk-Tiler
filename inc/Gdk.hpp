#ifndef _GDK_HPP_
#define _GDK_HPP_

#include <cassert>
#include <iostream>

#include <gdk/gdk.h>

class Gdk {
 private:
  GdkScreen *screen;

 public:
  Gdk(int argc, char *argv[]) {
    gdk_init(&argc, &argv);
    GdkDisplay *display = gdk_display_get_default();
    screen = gdk_display_get_screen(display, 0);
  };

  ~Gdk() {
  }

  GdkWindow *GetActiveWindow() {
    assert(screen != NULL);

    return gdk_screen_get_active_window(screen);
  }

  void GetWindowSize(GdkWindow *gdkWindow, gint &width, gint &height) {
    gdk_window_get_size(gdkWindow, &width, &height);
  }

  void ResizeWindow(GdkWindow *gdkWindow, gint width, gint height) {
    gdk_window_resize(gdkWindow, width, height);
  }

  void MoveToLeft() {
    assert(screen != NULL);

    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gint width = gdk_screen_get_width(screen);
    gint height = gdk_screen_get_height(screen);

    gdk_window_move_resize(gdkWindow, 0, 0, width / 2, height);
    gdk_window_geometry_changed(gdkWindow);
  }

  void MoveToRight() {
    assert(screen != NULL);

    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gint width = gdk_screen_get_width(screen);
    gint height = gdk_screen_get_height(screen);

    gdk_window_move_resize(gdkWindow, width / 2, 0, width / 2, height);
    gdk_window_geometry_changed(gdkWindow);
  }
};

#endif