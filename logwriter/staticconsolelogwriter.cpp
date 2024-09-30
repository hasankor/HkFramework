#include "staticconsolelogwriter.h"
#include <QStandardPaths>
#include "consolelogwriter.h"
#include <QMutex>
#include <QMutexLocker>


static QMutex mMessageMutex;
static ConsoleLogWriter *mCitLogWriter = nullptr;

void StaticConsoleLogWriter::consoleMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    QMutexLocker tMutexLocker(&mMessageMutex);

    if(mCitLogWriter == nullptr){
        QString tLogFilePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/" + qApp->applicationName() + "Log.txt";
        uint32_t tLogMaxMBSize = 50;
        uint8_t tLogFile = 3;
        mCitLogWriter = new ConsoleLogWriter(tLogFilePath, tLogMaxMBSize, tLogFile);
    }
    mCitLogWriter->consoleMessageOutput(type, context, msg);
}

StaticConsoleLogWriter::StaticConsoleLogWriter()
{

}
