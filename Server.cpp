#include "Server.h"
#include "socketrunnable.h"
#include <chrono>

Server::Server()
{
    countRequest_ = 0;
    if (this->listen(QHostAddress::Any, 4242))
    {
        qDebug() << "Server start successfully";
    }
    else
    {
        qDebug() << "Server start error";
    }
    threadPool_ = new QThreadPool(this);
    threadPool_->setMaxThreadCount(20);
}

Server::~Server()
{
    delete threadPool_;
    delete socket_;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket_ = new QTcpSocket;
    socket_->setSocketDescriptor(socketDescriptor);

    connect(socket_, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket_, &QTcpSocket::disconnected, socket_, &QTcpSocket::deleteLater);

    sockets_.insert(socketDescriptor, socket_);
    qDebug() << socketDescriptor << " client connected";
}

void Server::slotReadyRead()
{
    std::chrono::nanoseconds nanoseconds = getCurrentTime();
    if (countRequest_ == 0)
    {
        lastRequest_ = nanoseconds;
    }
    std::chrono::nanoseconds lastRequest = nanoseconds - lastRequest_;

    socket_ = (QTcpSocket*)sender();
    SocketRunnable* runnable = new SocketRunnable(socket_->socketDescriptor(), countRequest_++, lastRequest);
    lastRequest_ = nanoseconds;
    threadPool_->start(runnable);
}

std::chrono::nanoseconds Server::getCurrentTime()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
}
