cmake_minimum_required(VERSION 2.8.4)

project(Gtk-Tiler)

add_definitions(-DWNCK_I_KNOW_THIS_IS_UNSTABLE)

find_package(GTK2 2.0 REQUIRED gtk)

include_directories(${GTK2_INCLUDE_DIRS})

include_directories(
  ${PROJECT_SOURCE_DIR}
  )

set(SOURCE_FILES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${GTK2_LIBRARIES})