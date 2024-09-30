#include "logwriterbase.h"

#include "logwriter/spdlog/spdlog.h"
#include "logwriter/spdlog/async.h"

#include <QDebug>

LogWriterBase::LogWriterBase(QString pLoggerName, QString pFileName, QObject *parent)
    : QObject(parent)
    , mLoggerName(pLoggerName)
    , mFileName(pFileName)
    , mAsyncLogger(nullptr)
{
    // queue with 8k items and 1 backing thread.
    spdlog::init_thread_pool(8192, 1);
    spdlog::flush_every(std::chrono::seconds(1));
}

void LogWriterBase::setLevel(spdlog::level::level_enum pLevel)
{
    if(mAsyncLogger != nullptr){
        mAsyncLogger->set_level(pLevel);
    }
}

void LogWriterBase::setPattern(QString pPattern)
{
    if(mAsyncLogger != nullptr){
        mAsyncLogger->set_pattern(pPattern.toStdString());
    }
}

void LogWriterBase::handleWarning(QString pWarning)
{
    if(mAsyncLogger != nullptr){
        mAsyncLogger->warn(pWarning.toStdString());
    }
}

void LogWriterBase::handleError(QString pError)
{
    if(mAsyncLogger != nullptr){
        mAsyncLogger->error(pError.toStdString());
    }
}

void LogWriterBase::handleDebug(QString pDebug)
{
    if(mAsyncLogger != nullptr){
        mAsyncLogger->debug(pDebug.toStdString());
    }
}

void LogWriterBase::handleInfo(QString pInfo)
{
    if(mAsyncLogger != nullptr){
        mAsyncLogger->info(pInfo.toStdString());
    }
}

void LogWriterBase::handleCritical(QString pInfo)
{
    if(mAsyncLogger != nullptr){
        mAsyncLogger->critical(pInfo.toStdString());
    }
}

void LogWriterBase::handleTrace(QString pInfo)
{
    if(mAsyncLogger != nullptr){
        mAsyncLogger->trace(pInfo.toStdString());
    }
}

