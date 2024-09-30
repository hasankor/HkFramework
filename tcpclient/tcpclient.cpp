#include "tcpclient.h"
#include <QCoreApplication>
#include <QAbstractEventDispatcher>

#include <qtcpsocket.h>

TcpClient::TcpClient(QString pIp, short pPort)
    : AThread()
    , mSocket(nullptr)
    , mIp(pIp)
    , mPort(pPort)
{
    mHealthStatus = new HealthChecker(this, -1);
}

HealthChecker *TcpClient::healthStatus() const
{
    return mHealthStatus;
}

void TcpClient::writeMessage(QByteArray pBuffer)
{
    if(!mSocket){
        qDebug() << objectName() << "TcpSenderReceiver::writeMessagethread not started";
        return;
    }

    if(!makeMethodRunOnThisThread("writeMessage", Q_ARG(QByteArray, pBuffer))){
        return;
    }

    //    qDebug() << "Sent Message Begin | "<< pBuffer.toHex(':') << "End Sent Message";
    if(mSocket->state() == QTcpSocket::ConnectedState){
        mSocket->write(pBuffer);
    }
    else {
        qDebug() << objectName() << "TcpClient::writeMessag mSocket disconnected";
        reConnectToHost();
    }
}

void TcpClient::mainLoop()
{
    mSocket = new QTcpSocket(this);
    mSocket->connectToHost(mIp, mPort);

    QObject::connect(mSocket, &QTcpSocket::readyRead, this, [this](){
        QByteArray pbuf;

        while(mSocket->bytesAvailable())
            pbuf.append(mSocket->readAll());

        if(pbuf.length() != 0)
        {
            //  auto temp = chopAccordingHeader(pbuf);
            //   qDebug()<<  "Incoming Message:  "<<pbuf.toHex(':') << "  End Message " ;
            emit newMessage(pbuf);
        }
    });

    QObject::connect(mSocket,  &QTcpSocket::connected, this, [this](){
        qDebug() << objectName() << "TcpClient::mainLoop connected:";
        mHealthStatus->handleAliveMessage();
    });

    QObject::connect(mSocket,  &QTcpSocket::disconnected, this, [this](){
        qDebug() << objectName() << "TcpClient::mainLoop disconnected:";
        reConnectToHost();
    });

    while(!getShouldStop()) {
        QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);
    }

    mSocket->close();
    mSocket->deleteLater();
    mSocket = nullptr;
}

void TcpClient::reConnectToHost()
{
    mHealthStatus->handleKillMessage();

    qDebug() << objectName() << "TcpClient::reConnectToHost";
    QThread::msleep(1000);

    mSocket->connectToHost(mIp, mPort);
}

