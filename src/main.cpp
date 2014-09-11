#include <iostream>

#include "inc/Process.hpp"
#include "inc/Xlib.hpp"
#include "inc/Gtk.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  Process::Daemonize(NULL);

  Xlib xlib;
  Gdk gdk(argc, argv);
  Gtk gtk(argc, argv);

  gtk.SetTrayIcon();
  xlib.RegisterHotkey(gdk);

  return 0;
}