Introduction
============

A program that simulates ms windows' "Win + Arrow Key" behavior on linux system.

Screenshots
===========

![Screenshot](/screenshots/gtk-tiler.gif?raw=true "Gtk-Tiler")

Usage
=====

Start this program. It has no gui nor any hints. Click a window to make it focused. Now you can:

 - Press Shift + Alt + Left Arrow to place it at the left of the screen
 - or Press Shift + Alt + Right Arrow to place it at the right of the screen
 - or Press Shift + Alt + Up Arrow to maximize it
 - or Press Shift + Alt + Down Arrow to minimize it

You can press Shift + Alt + C to quit this program. Still, it quit quietly without any word.

Compile
=======

 - Install gtk2-devel and cmake.
 - Clone the source code into Gtk-Tiler directory
 - $ cd Gtk-Tiler && mkdir build && cd build && cmake .. && make (With GTK3)
 - $ cd Gtk-Tiler && mkdir build && cd build && cmake .. -DGTK3=OFF && make (With GTK2)
 - Run the binary file located at Gtk-Tiler/build/Gtk-Tiler

Known issues
============

 - borders of window may overlap
 - doesn't support multi-screens
