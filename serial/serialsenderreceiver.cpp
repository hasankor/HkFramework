#include "serialsenderreceiver.h"

#include <QCoreApplication>
#include <QAbstractEventDispatcher>

SerialSenderReceiver::SerialSenderReceiver(QString pPortName, QSerialPort::BaudRate pBaudRate, QSerialPort::DataBits pDataBits, QSerialPort::Parity pParity, QSerialPort::FlowControl pFlowControl, QSerialPort::StopBits pStopBits)
    : AThread()
    , mPortName(pPortName)
    , mBaudRate(pBaudRate)
    , mDataBits(pDataBits)
    , mParity(pParity)
    , mFlowControl(pFlowControl)
    , mStopBits(pStopBits)

{

}

void SerialSenderReceiver::send(QByteArray data)
{
    if(!isRunning()){
        qDebug() << this->objectName() << "BSerialSenderReceiver::send SerialSenderReceiver not working";
        emit errorOccurred("Serial Communication not working");
        return;
    }
    if(!makeMethodRunOnThisThread("send", Q_ARG(QByteArray, data))){
        return;
    }

    if(mSerialPort->write(data) == -1){
        qDebug() << this->objectName() << "BSerialSenderReceiver::send QByteArray error while sending data " << mSerialPort->error();
        emit errorOccurred(mSerialPort->errorString());
    }
}

void SerialSenderReceiver::mainLoop()
{
    mSerialPort = new QSerialPort(this);
    mSerialPort->setPortName(mPortName);

    if(!mSerialPort->setBaudRate(mBaudRate)){
        qDebug() << this->objectName() << "BSerialSenderReceiver::bind setBaudRate error " <<  mSerialPort->errorString();
        emit errorOccurred(mSerialPort->errorString()+ " " + QString(mBaudRate));
        return;
    }
    if(!mSerialPort->setDataBits(mDataBits)){
        qDebug() << this->objectName() << "BSerialSenderReceiver::bind setDataBits error " <<  mSerialPort->errorString();
        emit errorOccurred(mSerialPort->errorString()+ " " + QString(mDataBits));
        return;
    }
    if(!mSerialPort->setParity(mParity)){
        qDebug() << this->objectName() << "BSerialSenderReceiver::bind setParity error " <<  mSerialPort->errorString();
        emit errorOccurred(mSerialPort->errorString()+ " " + QString(mParity));
        return;
    }
    if(!mSerialPort->setFlowControl(mFlowControl)){
        qDebug() << this->objectName() << "BSerialSenderReceiver::bind setFlowControl error " <<  mSerialPort->errorString();
        emit errorOccurred(mSerialPort->errorString()+ " " + QString(mFlowControl));
        return;
    }
    if(!mSerialPort->setStopBits(mStopBits)){
        qDebug() << this->objectName() << "BSerialSenderReceiver::bind setStopBits error " <<  mSerialPort->errorString();
        emit errorOccurred(mSerialPort->errorString() + " " + QString(mStopBits));
        return;
    }
    if(!mSerialPort->open(QIODevice::ReadWrite)){
        qDebug() << this->objectName() << "BSerialSenderReceiver::bind open error " <<  mSerialPort->errorString();
        emit errorOccurred(mSerialPort->errorString() + " " + mPortName);
        return;
    }

    QObject::connect(mSerialPort, &QSerialPort::errorOccurred, this, &SerialSenderReceiver::error);
    QObject::connect(mSerialPort, &QSerialPort::readyRead, this, &SerialSenderReceiver::readyRead);

    while(!getShouldStop()) {
        QThread::currentThread()->eventDispatcher()->processEvents(QEventLoop::WaitForMoreEvents);
    }
    mSerialPort->close();
    mSerialPort->deleteLater();
}

void SerialSenderReceiver::error(QSerialPort::SerialPortError error)
{
    if(error != QSerialPort::TimeoutError){
        qDebug() << this->objectName() << "BSerialReceiver::errorOccurred error " << error;
        emit errorOccurred(QString(error));
    }
}

void SerialSenderReceiver::readyRead()
{
    emit newMessageFromRemote(mSerialPort->readAll());
}

