#ifndef _GTK_HPP_
#define _GTK_HPP_

#include <gtk/gtk.h>

class Gtk {
 public:
  Gtk(int argc, char *argv[]) {
    gtk_init(&argc, &argv);
  };

  void SetTrayIcon() {
    GtkStatusIcon *gtk_statusIcon = gtk_status_icon_new_from_stock(GTK_STOCK_INFO);

    assert (gtk_statusIcon != NULL);

    gtk_status_icon_set_tooltip_text(gtk_statusIcon, "gtk-tiler");
    // gtk_status_icon_set_blinking(gtk_statusIcon, true);
    gtk_status_icon_set_visible(gtk_statusIcon, true);

    GtkWidget *menu = gtk_menu_new(), *menu_exit_item = gtk_menu_item_new_with_label("Exit");
    g_signal_connect (G_OBJECT (menu_exit_item), "activate", G_CALLBACK (&Gtk::OnExit), NULL);
    gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_exit_item);
    gtk_widget_show_all(menu);

    g_signal_connect(GTK_STATUS_ICON (gtk_statusIcon), "popup-menu", G_CALLBACK (&Gtk::PopupMenu), menu);
  }

  void Run() {
    SetTrayIcon();
    gtk_main();
  }

  static void PopupMenu(GtkStatusIcon *gtk_statusIcon, guint button, guint32 activate_time, gpointer popup_menu) {
    gtk_menu_popup(GTK_MENU(popup_menu), NULL, NULL, gtk_status_icon_position_menu, gtk_statusIcon, button, activate_time);
  }

  static void OnExit() {
    Xlib::SendQuitKeyEvent();
  }
};

#endif // _GTK_HPP_