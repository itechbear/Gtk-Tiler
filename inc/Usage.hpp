#ifndef _USAGE_HPP_
#define _USAGE_HPP_

#include <cstdio>

class Usage {
 public:
  static void usage(int argc, char *argv[]) {
    bool need_print = false;

    for (int i = 1; i < argc; i++) {
      if (string(argv[i]) == "-h" || string(argv[i]) == "--help") {
        need_print = true;
        break;
      }
    }

    if (!need_print) {
      return;
    }

    fprintf(stdout, "Usage: \n");
    fprintf(stdout, "    %s -i [file] : specify a tray icon file\n", argv[0]);
    fprintf(stdout, "    %s -h,--help : show this help\n", argv[0]);
    fprintf(stdout, "Example: \n");
    fprintf(stdout, "    %s -i /usr/share/icons/gnome/32x32/status/info.png\n", argv[0]);

    exit(0);
  };
};

#endif // _USAGE_HPP_