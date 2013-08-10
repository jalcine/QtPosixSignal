cmake_minimum_required(VERSION 2.8)
project(QtPosixSignal)

# Add our modules to the path.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

# Include some of our modules.
include(CMakeProvideUninstallTarget)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(doc)
