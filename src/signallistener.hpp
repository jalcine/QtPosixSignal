#ifndef QTPOSIXSIGNAL_SIGNALLISTENER_HPP
#define QTPOSIXSIGNAL_SIGNALLISTENER_HPP

#include <QtCore/QObject>

namespace QtPosixSignal {
  class SignalListenerPrivate;
  class SignalListener : public QObject {
    Q_OBJECT;
    Q_DISABLE_COPY(SignalListener);
    Q_DECLARE_PRIVATE(SignalListener);

    public:
      SignalListener(QObject* parent);
      virtual ~SignalListener();

      /**
       * @fn handleSignal
       *
       * This signal is emitted when a POSIX signal is recieved internally.
       */
      Q_SIGNAL void signalReceived();
  };
}

#endif
