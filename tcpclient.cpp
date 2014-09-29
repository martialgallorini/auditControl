#include "tcpclient.h"
#include <QDebug>


TCPClient::TCPClient(QObject *parent) :
    QObject(parent)
{
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    timer = new QTimer(this);
    timeout = 240000; // timeout in milliseconds
    connect(timer, SIGNAL(timeout()), this, SLOT(keepAlive()));
}

TCPClient::~TCPClient()
{
    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        socket->abort();
    }
    delete socket;
}

bool TCPClient::connection(QString _addr, int _port)
{
    addr = _addr;
    port = _port;

    socket->connectToHost(addr, port);

    if(!socket->waitForConnected(2000))
    {
        qWarning() << "Can't connect to : " << addr << " on port " << port;
        return false;
    }
    return true;
}

bool TCPClient::sendCommand(QByteArray command)
{
    if (socket->state() != QAbstractSocket::ConnectedState)
    {
        qWarning() << "Can't send command : not connected !";
        return false;
    }
    if(socket->write(command))
    {
        QString resp;
        if(socket->waitForBytesWritten(2000) && socket->waitForReadyRead((2000)))
        {
            while(socket->bytesAvailable() > 0)
            {
                resp.append(socket->readLine());
            }
        }
    }
    timer->start(timeout);
    return true;
}

QByteArray TCPClient::sendQuery(QByteArray query)
{
    if (socket->state() != QAbstractSocket::ConnectedState)
    {
        qWarning() << "Can't send query : not connected !";
        return QByteArray("ERR_NOT_CONNECTED");
    }
    if(socket->write(query))
    {
        QByteArray resp;
        if(socket->waitForBytesWritten(2000) && socket->waitForReadyRead((2000)))
        {
            while(socket->bytesAvailable() > 0 && !resp.contains("@"))
            {
                resp.append(socket->readLine());
            }
            timer->start(timeout);
            return resp;
        }
        else
        {
            qWarning() << "Waiting for data to read timed out. Nothing to read !";
        }
        return QByteArray();
    }
    qWarning() << "Warning : problem sending query !";
    return QByteArray("ERR_SEND_QUERY");
}

int TCPClient::isConnected()
{
    return socket->state();
}

void TCPClient::closeConnection()
{
    socket->abort();
}

// SLOTS ------------------

void TCPClient::connected()
{
    if(socket->waitForReadyRead((2000)))
    {
        // purge buffer
        while(socket->bytesAvailable() > 0)
        {
            socket->readLine();
        }
    }
    timer->start(timeout);
    emit sigConnected();
}

void TCPClient::disconnected()
{
    emit sigDisconnected();
}

void TCPClient::keepAlive()
{
    sendCommand("?\n");
}

