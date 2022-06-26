#include "socketrunnable.h"

SocketRunnable::SocketRunnable(qintptr socketDescriptor, qint16 countRequest,
                               std::chrono::nanoseconds requestTime)
    : socketDescriptor_(socketDescriptor), countRequest_(countRequest), requestTime_(requestTime)
{

}

void SocketRunnable::run()
{
    socket_ = new QTcpSocket;
    socket_->setSocketDescriptor(socketDescriptor_);
    QString response = QString::number(countRequest_) + "; "
            + QString::number(requestTime_.count());
    socket_->write(response.toUtf8());
    qDebug() << QString::number(countRequest_) << " send to " << socketDescriptor_;
    socket_->close();
    socket_->deleteLater();
}
