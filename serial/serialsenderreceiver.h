#ifndef SERIALSENDERRECEIVER_H
#define SERIALSENDERRECEIVER_H

#include <thread/athread.h>
#include <QSerialPort>

class SerialSenderReceiver : public AThread
{
    Q_OBJECT
public:
    SerialSenderReceiver(QString pPortName, QSerialPort::BaudRate pBaudRate, QSerialPort::DataBits pDataBits = QSerialPort::DataBits::Data8,
                          QSerialPort::Parity pParity = QSerialPort::Parity::NoParity, QSerialPort::FlowControl pFlowControl = QSerialPort::FlowControl::NoFlowControl,
                          QSerialPort::StopBits pStopBits  = QSerialPort::StopBits::OneStop);

signals:
    void errorOccurred(QString pError);
    void newMessageFromRemote(QByteArray message);

public slots:
    void send(QByteArray data);

    // AThread interface
protected:
    void mainLoop() override;

private slots:
    void error(QSerialPort::SerialPortError error);
    void readyRead();


private:
    QString mPortName;
    QSerialPort::BaudRate mBaudRate;
    QSerialPort::DataBits mDataBits;
    QSerialPort::Parity mParity;
    QSerialPort::FlowControl mFlowControl;
    QSerialPort::StopBits mStopBits;
    QSerialPort *mSerialPort;
};

#endif // SERIALSENDERRECEIVER_H


//QSerialPort *serial = new QSerialPort;
////Set serial port name
//serial->setPortName(name);
////Open serial port
//serial->open(QIODevice::ReadWrite);
////set baud rate
//serial->setBaudRate(BaudRate);
////Set the number of data bits
//serial->setDataBits(QSerialPort::Data8);
// //Set parity
// serial->setParity(QSerialPort::NoParity);
////Set stop bit
//serial->setStopBits(QSerialPort::OneStop);
////set flow control
//serial->setFlowControl(QSerialPort::NoFlowControl);
