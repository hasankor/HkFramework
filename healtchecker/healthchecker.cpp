#include "healthchecker.h"

#include <QDateTime>
#include <QDebug>
HealthChecker::HealthChecker(QObject *parent, const int &pCheckIntervalMS, const int &pTimeoutMS)
    : QObject(parent)
    , mTimeoutMs(pTimeoutMS)
    , mTimer(nullptr)
    , mConnectionStatus(Enums::ConnectionStatus::DIS_CONNECTED)
{
    if(pCheckIntervalMS != -1){
        mLastMessageTimeMS = QDateTime::currentMSecsSinceEpoch();
        mTimer = new QTimer(this);
        QObject::connect(mTimer, &QTimer::timeout, this, &HealthChecker::checkComponentAlive);
        mTimer->start(pCheckIntervalMS);
    }
    else{
        setConnectionStatus(Enums::ConnectionStatus::CONNECTED);
    }
}

Enums::ConnectionStatus HealthChecker::connectionStatus() const
{
    return mConnectionStatus;
}

void HealthChecker::handleAliveMessage()
{
    mLastMessageTimeMS = QDateTime::currentMSecsSinceEpoch();
}

void HealthChecker::handleKillMessage()
{
    setConnectionStatus(Enums::ConnectionStatus::DIS_CONNECTED);
}

void HealthChecker::setConnectionStatus(Enums::ConnectionStatus pConnectionStatus)
{
    if (mConnectionStatus == pConnectionStatus)
        return;

    mConnectionStatus = pConnectionStatus;
    emit connectionStatusChanged(mConnectionStatus);
}

void HealthChecker::checkComponentAlive()
{
    Enums::ConnectionStatus tStatus = Enums::ConnectionStatus::CONNECTED;

    if((QDateTime::currentDateTime().toMSecsSinceEpoch() - mLastMessageTimeMS) > mTimeoutMs){
        tStatus = Enums::ConnectionStatus::DIS_CONNECTED;
    }

    setConnectionStatus(tStatus);
}
