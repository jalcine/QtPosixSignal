# QtPosixSignal

POSIX signal processing for Qt made simple.

## Abstract

All of those people writing kickass applications in Qt typically don't bother 
with POSIX signals. They have other worries than something calling a force-quit 
on their application. I wrote this library as a bit of a "ease-of-use" factor 
for those of us who needed to interact with POSIX operations.

## Requirements

Right now, you just need [Qt](http://qt-project.org) and the
`<signal.h>` header on your POSIX-capable system.

## Usage

Using `QtPosixSignal` is meant to simple as possible while using as much of 
the Qt infrastructre as possible. This is done by using `QCoreApplication`'s 
event structure to dispatch the signal as *events* in the platforms so that 
developers can add an event filter to `QCoreApplication`. 

```c++
// Declare the handling object.
FooQObject obj;
QtPosixSignal::SignalListener listener(obj);

// Register the object.
listener.listenForSignals(obj);

// Register the object for a specific signal.
listener.listenForSignal(obj, SIGTERM);

```

By using `QtPosixSignal::SignalListener`, you can easily disable/enable your 
specific listeners with `stop()`/`start()`; thus allowing for a seamless 
interaction. All of the event listening and registering is abstracted away 
into the more friendly slots and signals system, so one can merely listen to 
a signal with the following signature as a slot:

```c++
// function signature.
void functionname(uint const signal)
```

```c++
// object.hpp
class Object : QObject {
  QOBJECT;
  QtPosixSignal::SignalListener* listener;
  public:
    explicit Object(QObject* parent);
    virtual ~Object();

    Q_SLOT void caughtSignal(uint const signal);
    void stop();
    void start();
};

// object.cpp
#include "object.hpp"
#include <QtCore/QDebug>

Object::Object(QObject* parent) : QObject(parent), listener(this) {
  listener->listenForSignals();
}

void Object::stop() {
  listener->stop();
}

void Object::start() {
  listener->start();
}

void Object::caughtSignal(uint const signal){ 
  qDebug() << "Caught signal: " << signal;  
}
```

The passing of the event loop back up the main event loop is done by 
`QtPosixSignal` so developers don't have to concern (or run the risk of 
corrupting) the event loop crashing.

## TODO
 + Test.
  + Add testing environment.
   + Incorporate CDash.
   + Incorporate (Travis.CI)[http://travis-ci.org]
  + Test with different versions of Qt.
   + Test with Qt4.
   + Test with Qt5.
  + Test on different platforms.
   + Test on Linux.
   + Test on BSD.
   + Test on OSX.
 + Work on properly determining the list of listeners when invoked.
  + on the `QtPosixSignal::SignalListener` level.
  + on a class-specific level.
  + on a global level.

## License
This code is licensed under the MIT license. We're all nice people, right?

## Author
`QtPosixSignal` was written by [Jacky Alcine](me@jalcine.me).
