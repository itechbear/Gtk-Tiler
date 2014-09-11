#include <iostream>

#include "inc/Lock.hpp"
#include "inc/Process.hpp"
#include "inc/Xlib.hpp"

using namespace std;

int main(int argc, char *argv[]) {
  Process::Daemonize(NULL);

  Lock lock;
  Xlib xlib;
  Gdk gdk(argc, argv);

  xlib.RegisterHotkey(gdk);

  return 0;
}