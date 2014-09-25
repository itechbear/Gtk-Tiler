#ifndef _CONFIG_HPP_
#define _CONFIG_HPP_

#include <string>

#include <X11/Xlib.h>
#include "Xlib.hpp"

class Config {
 public:
  static const std::string GetApplicationName() {
    return "Gtk-Tiler";
  }

  static const std::string GetBinaryName() {
    return "gtk-tiler";
  }

  static const std::string GetApplicationVersion() {
    return "1.0";
  }

  static const std::string GetWebsiteUrl () {
    return "http://github.com/itechbear/Gtk-Tiler";
  }

  static const std::string GetLicense() {
    return "GPL v3";
  }

  static const std::string GetCopyright() {
    return "copyright @ itechbear";
  }
};

#endif // _CONFIG_HPP_