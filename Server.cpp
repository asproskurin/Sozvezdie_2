#include "Server.h"
#include "socketthread.h"

#include <chrono>

Server::Server()
{
    countRequest_ = 0;
    correctRequest_ = "next";
    if (this->listen(QHostAddress::Any, 4242))
    {
        qDebug() << "Server start successfully";
    }
    else
    {
        qDebug() << "Server start error";
    }
}

Server::~Server()
{
    delete threadPool_;
    delete socket_;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket_ = new QTcpSocket;
    lastRequest_ = getCurrentTime();
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

    QDataStream in(socket_);
    in.setVersion(QDataStream::Qt_6_3);

    if (in.status() == QDataStream::Ok)
    {
        data_.clear();
        QString str;
        in >> str;
        if (str == correctRequest_)
        {
            SocketThread* thread = new SocketThread(socket_->socketDescriptor(), countRequest_);
            connect(thread, &SocketThread::requestDone, this, &Server::slotRequestAnswer);
            connect(thread, &SocketThread::finished, thread, &SocketThread::deleteLater);
            thread->start();
        }
    }
    else
    {
        qDebug() << "Data stream error";
    }
}

void Server::slotRequestAnswer(qintptr socketDescriptor,
                               qint16 countRequest, std::chrono::nanoseconds requestTime)
{
    socket_ = sockets_.value(socketDescriptor);
    QString response = QString::number(countRequest_) + "; "
            + QString::number((requestTime - lastRequest_).count());
    QByteArray data;
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_3);
    out << response;
    socket_->write(data);
    qDebug() << QString::number(countRequest_) << " send to " << socketDescriptor;
    lastRequest_ = requestTime;
    countRequest_ = countRequest;
}

std::chrono::nanoseconds Server::getCurrentTime()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
}
