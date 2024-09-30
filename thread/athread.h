#ifndef ATHREAD_H
#define ATHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>

class AThread : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)
public:
    AThread();
    virtual ~AThread();

    bool isRunning() const; // status check

public slots:    
    void start();
    void stop();

signals:
    void isRunningChanged(bool isRunning);

protected:
    // derived must use this for mainLoop!
    virtual void mainLoop() = 0;
    // use this for exiting mainloop, like: while(!getShouldStop()) ...
    bool getShouldStop() const;
    // may be used for self-stop
    void exitThreadLoop();

protected:
    //Args format must be Q_ARG(type_of_Variable, variable)
    template<typename ...Args>
    bool makeMethodRunOnThisThread(const char *methodName, Args... args){
        static_assert(sizeof...(args) <= MAX_ARGUMENT_COUNT, "You can't have more than 10 arguments!");

        if (thread() == QThread::currentThread()) { // if method is called in thisthread context, just return true
            return true;
        } // else invoke method in thisthread context, return false

        QVector<QGenericArgument> tGenericArgumentLis(MAX_ARGUMENT_COUNT, QGenericArgument(nullptr));
        const QVector<QGenericArgument> tTemplist = {args ...};

        for (int index = 0; index < tTemplist.size(); ++index) {
            tGenericArgumentLis[index] = tTemplist.at(index);
        }

        QMetaObject::invokeMethod(this, methodName,
                                  tGenericArgumentLis.at(0), tGenericArgumentLis.at(1), tGenericArgumentLis.at(2),
                                  tGenericArgumentLis.at(3), tGenericArgumentLis.at(4), tGenericArgumentLis.at(5),
                                  tGenericArgumentLis.at(6), tGenericArgumentLis.at(7), tGenericArgumentLis.at(8),
                                  tGenericArgumentLis.at(9));

        return false;
    }

private slots:
    void setIsRunning(bool isRunning);
    void outerLoop();

private:
    QThread mThread;
    bool mIsRunning = false;
    bool shouldStop = false;

private:
    const static int MAX_ARGUMENT_COUNT = 10;
};

#endif // ATHREAD_H
