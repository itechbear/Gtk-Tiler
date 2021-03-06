#ifndef _GDK_HPP_
#define _GDK_HPP_

#include <cassert>
#include <iostream>
#include <vector>

#include <gdk/gdk.h>

using std::vector;

class Gdk {
 private:
  GdkDisplay *display;
 public:
  Gdk(int argc, char *argv[]) {
    gdk_init(&argc, &argv);
    gdk_threads_init();
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

  gint GetMonitorsCount() {
    GdkScreen *gdkScreen = GetScreen();

    return gdk_screen_get_n_monitors(gdkScreen);
  }

  void GetMonitorsXYCordinate(vector<gint> &x, vector<gint> &y) {
    GdkScreen *gdkScreen = GetScreen();
    gint count = GetMonitorsCount();

    for (int i = 0; i < count; i++) {
      GdkRectangle gdkRectangle;
      gdk_screen_get_monitor_geometry(gdkScreen, i, &gdkRectangle);
      x.push_back(gdkRectangle.x);
      y.push_back(gdkRectangle.y);
    }
  }

  gint GetMonitorIndex(GdkWindow *gdkWindow) {
    GdkScreen *gdkScreen = GetScreen();

    return gdk_screen_get_monitor_at_window(gdkScreen, gdkWindow);
  }

  gint GetMonitorWidthHeightAt(int i, gint &x, gint &y, gint &width, gint &height) {
    GdkScreen *gdkScreen = GetScreen();

    GdkRectangle gdkRectangle;
    gdk_screen_get_monitor_geometry(gdkScreen, i, &gdkRectangle);

    x = gdkRectangle.x;
    y = gdkRectangle.y;
    width = gdkRectangle.width;
    height = gdkRectangle.height;
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

  void GetAvailableWidthAndHeight(GdkWindow *gdkWindow, gint &x, gint &y, gint &width, gint &height) {
    GdkScreen *gdkScreen = GetScreen();
    int index = GetMonitorIndex(gdkWindow);

    GetMonitorWidthHeightAt(index, x, y, width, height);
  }

  void MoveToLeft() {
    gdk_threads_enter();

    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gint x, y, width, height;
    GetAvailableWidthAndHeight(gdkWindow, x, y, width, height);
    gdk_window_unmaximize(gdkWindow);
    gdk_window_move_resize(gdkWindow, x, y, width / 2, height);
    Flush(gdkWindow);

    gdk_threads_leave();
  }

  void MoveToRight() {
    gdk_threads_enter();

    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gint x, y, width, height;
    GetAvailableWidthAndHeight(gdkWindow, x, y, width, height);
    gdk_window_unmaximize(gdkWindow);
    gdk_window_move_resize(gdkWindow, x + width / 2, y, width / 2, height);
    Flush(gdkWindow);

    gdk_threads_leave();
  }

  void Maximize() {
    gdk_threads_enter();

    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gdk_window_maximize(gdkWindow);
    Flush(gdkWindow);

    gdk_threads_leave();
  }

  void Minimize() {
    gdk_threads_enter();

    GdkWindow *gdkWindow = GetActiveWindow();

    assert(gdkWindow != NULL);

    gdk_window_iconify(gdkWindow);
    Flush(gdkWindow);

    gdk_threads_leave();
  }
};

#endif