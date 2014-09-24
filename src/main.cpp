#include <iostream>

#include "inc/Lock.hpp"
#include "inc/Process.hpp"
#include "inc/Xlib.hpp"
#include "inc/Gtk.hpp"
#include "inc/Thread.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  // Process::Daemonize(NULL);

  Lock lock;
  Gdk gdk(argc, argv);

  Xlib xlib(gdk);
  Gtk gtk(argc, argv, xlib);
  Thread thread(xlib);

  assert(thread.Start() == 0);

  gtk.SetTrayIcon();
  gtk_main();

  return 0;
}