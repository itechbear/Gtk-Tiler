#ifndef _GTK_HPP_
#define _GTK_HPP_

#include <string>
#include <gtk/gtk.h>

#include "inc/Config.hpp"

class Gtk {
 private:
  std::string icon_file_;

 public:
  Gtk(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    int i = 1;
    while (i < argc) {
      if (std::string(argv[1]) == "-i" && i < argc - 1) {
        icon_file_ = argv[i + 1];
        i += 2;
      } else {
        i++;
      }
    }
  };

  void SetTrayIcon() {
    GtkStatusIcon *gtk_statusIcon;

    if (!icon_file_.empty()) {
      gtk_statusIcon = gtk_status_icon_new_from_file(icon_file_.c_str());
    } else {
      gtk_statusIcon = gtk_status_icon_new_from_stock(GTK_STOCK_INFO);
    }

    if (gtk_statusIcon == NULL) {
      return;
    }

    gtk_status_icon_set_tooltip_text(gtk_statusIcon, Config::GetApplicationName().c_str());
    // gtk_status_icon_set_blinking(gtk_statusIcon, true);
    gtk_status_icon_set_visible(gtk_statusIcon, true);


    GtkWidget *menu = gtk_menu_new(),
        *menu_about_item = gtk_menu_item_new_with_label("About"),
        *menu_exit_item = gtk_menu_item_new_with_label("Exit");

    g_signal_connect (G_OBJECT (menu_about_item), "activate", G_CALLBACK (&Gtk::OnAbout), NULL);
    g_signal_connect (G_OBJECT (menu_exit_item), "activate", G_CALLBACK (&Gtk::OnExit), NULL);

    gtk_menu_shell_append (GTK_MENU_SHELL (menu), menu_about_item);
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

  static void OnAbout() {
    GtkWidget*  gtkWindow = gtk_about_dialog_new();
    gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(gtkWindow), Config::GetApplicationName().c_str());
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(gtkWindow), Config::GetApplicationVersion().c_str());
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(gtkWindow), Config::GetCopyright().c_str());
    gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(gtkWindow), Config::GetLicense().c_str());
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(gtkWindow), Config::GetWebsiteUrl().c_str());
    gtk_show_about_dialog(NULL, NULL);
  }

  static void OnExit() {
    Xlib::SendQuitKeyEvent();
  }
};

#endif // _GTK_HPP_