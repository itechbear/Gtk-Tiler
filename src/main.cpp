#include <iostream>

#include "inc/Lock.hpp"
#include "inc/Process.hpp"
#include "inc/Xlib.hpp"
#include "inc/Gtk.hpp"
#include "inc/Thread.hpp"
#include "inc/Usage.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  Usage::usage(argc, argv);

  Process::Daemonize(NULL);

  Lock lock;
  Xlib xlib(argc, argv);
  Gtk gtk(argc, argv);
  Thread thread(xlib);

  assert(thread.Start() == 0);

  gtk.Run();

  return 0;
}