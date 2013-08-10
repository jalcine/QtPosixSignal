#include "signallistener.hpp"
#include "private/signallistener.hpp"
#include <QtCore/QSocketNotifier>

using QtPosixSignal::SignalListener;
using QtPosixSignal::SignalListenerPrivate;

SignalListener::SignalListener(QObject* parent) :
  QObject(parent), d_ptr(new SignalListenerPrivate(this)) {
}

void SignalListener::listenForSignal(const uint signal) {
  // TODO: Clear out previous logic.
  Q_D(SignalListener);
  d->clear();

  d->socket = new QSocketNotifier(d->fd[1], QSocketNotifier::Read, this);
  connect(d->socket, SIGNAL(activated(int)), this, SLOT(handleSignal()));
}

void SignalListener::handleSignal(){
  Q_D(SignalListener);

  // Disable the socket momentarily.
  d->socket->setEnabled(false);

  char tmp;
  ::read(d->fd[1], &tmp, sizeof(tmp));

  // Invoke Qt signal for me, please!
  this->signalReceived();

  // And back down to UNIX.
  d->socket->setEnabled(true);
}

SignalListener::~SignalListener() {
  Q_D(SignalListener);
  
  // Clean up our work with the notifier.
  d->socket->setEnabled(false);
  d->socket->deleteLater();

  free(fd[1]);
  free(fd[0]);
}

#include "signallistener.moc"
