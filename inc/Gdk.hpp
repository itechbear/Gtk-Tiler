#ifndef _GDK_HPP_
#define _GDK_HPP_

#include <cassert>
#include <iostream>

#include <gdk/gdk.h>

class Gdk {
 private:
  GdkDisplay *display;
 public:
  Gdk(int argc, char *argv[]) {
    gdk_init(&argc, &argv);
    display = gdk_display_get_default();
  };

  ~Gdk() {
  }

  GdkScreen *GetScreen() {
    return gdk_display_get_screen(display, 0);
  }

  GdkWindow *GetActiveWindow() {
    GdkScreen *gdkScreen = GetScreen();

    return gdk_screen_get_active_window(gdkScreen);
  }

  void GetWindowSize(GdkWindow *gdkWindow, gint &width, gint &height) {
    gint x, y, depth;
#if GDK_MAJOR_VERSION == 3
      gdk_window_get_geometry(gdkWindow, &x, &y, &width, &height);
#else
      gdk_window_get_geometry(gdkWindow, &x, &y, &width, &height, &depth);
#endif
  }

  void ResizeWindow(GdkWindow *gdkWindow, gint width, gint height) {
    gdk_window_resize(gdkWindow, width, height);
  }

  static void Flush(GdkWindow *gdkWindow) {
    gdk_flush();
  }

  void GetAvailableWidthAndHeight(gint &width, gint &height) {
    GdkScreen *gdkScreen = GetScreen();

    width = gdk_screen_get_width(gdkScreen);
    height = gdk_screen_get_height(gdkScreen);
  }

  void MoveToLeft() {
    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gint width, height;
    GetAvailableWidthAndHeight(width, height);
    gdk_window_unmaximize(gdkWindow);
    gdk_window_move_resize(gdkWindow, 0, 0, width / 2, height);
    Flush(gdkWindow);
  }

  void MoveToRight() {
    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gint width, height;
    GetAvailableWidthAndHeight(width, height);
    gdk_window_unmaximize(gdkWindow);
    gdk_window_move_resize(gdkWindow, width / 2, 0, width / 2, height);
    Flush(gdkWindow);
  }

  void MoveToUp() {
    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gdk_window_maximize(gdkWindow);
    Flush(gdkWindow);
  }

  void MoveToDown() {
    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gdk_window_iconify(gdkWindow);
    Flush(gdkWindow);
  }
};

#endif