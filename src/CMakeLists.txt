find_package(Qt4 COMPONENTS
  QtCore REQUIRED)

include_directories(${QT_QTCORE_INCLUDE_DIR})

set(QtPosixSignal_SRCS
  signallistener.cpp)
set(QtPosixSignal_HDRS
  SignalListener
  signallistener.hpp)

qt4_automoc(${QtPosixSignal_SRCS})

add_library(QtPosixSignal SHARED ${QtPosixSignal_SRCS})

target_link_libraries(QtPosixSignal ${QT_QTCORE_LIBRARY})
