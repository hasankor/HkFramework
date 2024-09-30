#include "athread.h"

#include <QDebug>
#include <QAbstractEventDispatcher>

AThread::AThread()
    : QObject(nullptr)
    , mIsRunning(false)
{
}

AThread::~AThread() {
    stop();
//    moveToThread(QThread::currentThread());
}

void AThread::start() {
    if(mIsRunning) {
        return;
    }

    shouldStop = false;

    moveToThread(&mThread);
    connect(&mThread, SIGNAL(started()), this, SLOT(outerLoop()));
    mThread.start();
}

void AThread::exitThreadLoop()
{
    shouldStop = true;
    if(mThread.eventDispatcher())
        mThread.eventDispatcher()->wakeUp();
}

void AThread::stop() {
    if(!mIsRunning){
        return;
    }

    exitThreadLoop();

    mThread.wait();
}

bool AThread::isRunning() const
{
    return mIsRunning;
}

void AThread::setIsRunning(bool isRunning)
{
    if (mIsRunning == isRunning)
        return;

    mIsRunning = isRunning;
    emit isRunningChanged(mIsRunning);
}

void AThread::outerLoop() {
    setIsRunning(true);

    mainLoop();

    mThread.quit();
    disconnect(&mThread, SIGNAL(started()), this, SLOT(outerLoop()));

    setIsRunning(false);
}

bool AThread::getShouldStop() const
{
    return shouldStop;
}
