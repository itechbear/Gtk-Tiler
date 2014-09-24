Introduction
============

A program that simulates ms windows' "Win + Arrow Key" behavior on linux system.

Screenshots
===========

![Screenshot](/screenshots/gtk-tiler.gif?raw=true "Gtk-Tiler")

Usage
=====

Start this program. It minimizes itself to system tray. Click a window to make it focused. Now you can:

 - Press Meta(Aka, Win/Super) + Left Arrow to place it at the left of the screen
 - or Press Meta(Aka, Win/Super) + Right Arrow to place it at the right of the screen
 - or Press Meta(Aka, Win/Super) + Up Arrow to maximize it
 - or Press Meta(Aka, Win/Super) + Down Arrow to minimize it

You can press Meta(Aka, Win/Super) + C to quit this program, Or through the menu of the tray icon.

Compile
=======

 - Install gtk2-devel/gtk3-devel and cmake.
 - Clone the source code into Gtk-Tiler directory
 - $ cd Gtk-Tiler && mkdir build && cd build && cmake .. && make (With GTK3)
 - $ cd Gtk-Tiler && mkdir build && cd build && cmake .. -DGTK3=OFF && make (With GTK2)
 - Run the binary file located at Gtk-Tiler/build/Gtk-Tiler

Known issues
============

 - doesn't support multi-screens
 - gdk_screen_get_monitor_at_window() sometimes returns a wrong value for some application, eg. chromium-browser.
