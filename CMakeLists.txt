cmake_minimum_required(VERSION 2.8.4)

project(Gtk-Tiler)

option(GTK3 "Build with GTK3 instead of GTK2" ON)

find_package(PkgConfig REQUIRED)

if (GTK3)
  pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
  include_directories(${GTK3_INCLUDE_DIRS})
else()
  pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
  include_directories(${GTK2_INCLUDE_DIRS})
endif()

include_directories(
  ${PROJECT_SOURCE_DIR}
  )

set(SOURCE_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (GTK3)
  target_link_libraries(${PROJECT_NAME} ${GTK3_LIBRARIES})
else()
  target_link_libraries(${PROJECT_NAME} ${GTK2_LIBRARIES})
endif()

