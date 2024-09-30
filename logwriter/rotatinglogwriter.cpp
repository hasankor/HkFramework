#include "rotatinglogwriter.h"

#include "logwriter/spdlog/sinks/rotating_file_sink.h"
#include "logwriter/spdlog/async.h"

#include <QDebug>

RotatingLogWriter::RotatingLogWriter(QString pLoggerName, QString pFileName, uint32_t pMaxMBSize, uint8_t pMaxFiles, QObject *parent)
    : LogWriterBase(pLoggerName, pFileName, parent)
{
    try
    {
        mAsyncLogger = spdlog::rotating_logger_mt<spdlog::async_factory>(mLoggerName.toStdString(), mFileName.toStdString(), (pMaxMBSize * ONE_MB), pMaxFiles);
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        mAsyncLogger = nullptr;
        qDebug() << "BRotatingLogWriter::BRotatingLogWriter rotating_logger_mt Log init failed: " << ex.what();
    }
}
