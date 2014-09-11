#ifndef _GTK_HPP_
#define _GTK_HPP_

#include <gtk/gtk.h>

class Gtk {
 public:
  Gtk(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
  };

  ~Gtk() {

  }

  void SetTrayIcon() {
    gchar const *icon_file = "/usr/share/icons/gnome/scalable/status/info.svg";
    GtkStatusIcon *gtkStatusIcon = gtk_status_icon_new_from_file(icon_file);
    gtk_status_icon_set_visible(gtkStatusIcon, true);
  }
};

#endif