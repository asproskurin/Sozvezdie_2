#include "Server.h"

Server::Server()
{
    countRequest = 0;
    if (this->listen(QHostAddress::Any, 4242))
    {
        qDebug() << "Server start successfully";
    }
    else
    {
        qDebug() << "Server start error";
    }
    threadPool = new QThreadPool(this);
    threadPool->setMaxThreadCount(20);
}

Server::~Server()
{
    delete threadPool;
    delete socket;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sockets.insert(socketDescriptor, socket);
    qDebug() << socketDescriptor << " client connected";
}

void Server::slotReadyRead()
{

}
