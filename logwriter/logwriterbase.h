#ifndef LOGWRITERBASE_H
#define LOGWRITERBASE_H

#include <QObject>
#include <memory>
#include <logwriter/spdlog/common.h>
#include <logwriter/spdlog/logger.h>

class LogWriterBase : public QObject
{
    Q_OBJECT
public:
    explicit LogWriterBase(QString pLoggerName, QString pFileName, QObject *parent);

public slots:
    void handleWarning(QString pWarning);
    void handleError(QString pError);
    void handleDebug(QString pDebug);
    void handleInfo(QString pInfo);
    void handleCritical(QString pInfo);
    void handleTrace(QString pInfo);

protected:
    // Set global log level to debug
    void setLevel(spdlog::level::level_enum pLevel);
    void setPattern(QString pPattern);

protected:
    // child must allocate this with the logger type it wants
    std::shared_ptr<spdlog::logger> mAsyncLogger;
    QString mLoggerName, mFileName;
};

#endif // LOGWRITERBASE_H
