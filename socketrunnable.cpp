#include "socketrunnable.h"

socketRunnable::socketRunnable(QTcpSocket* socket, qint16 countRequest,
                               std::chrono::nanoseconds requestTime)
    : socket_(socket), countRequest_(countRequest), requestTime_(requestTime)
{

}

void socketRunnable::run()
{
    socket_->waitForReadyRead();
    qDebug() << socket_->readAll();

    QString response = QString::number(countRequest_) + "; "
            + QString::number(requestTime_.count());
    socket_->write(response.toUtf8());
}
