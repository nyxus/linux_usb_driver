cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(Gcv-usb-app VERSION 0.1.0)
add_executable(Gcv-usb-app main.cpp gcv-usb-app.cpp)

# Set project config, E.g. version number
configure_file(Config.h.in Config.h)
target_include_directories(Gcv-usb-app PUBLIC
						   "${PROJECT_BINARY_DIR}"
						   )

