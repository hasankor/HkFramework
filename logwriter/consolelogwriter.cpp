#include "consolelogwriter.h"

ConsoleLogWriter::ConsoleLogWriter(QString pFileName, uint32_t pMaxMBSize, uint8_t pMaxFiles, QObject *parent)
    : RotatingLogWriter("CONSOLE_LOG", pFileName, pMaxMBSize, pMaxFiles, parent)
{
    setLevel(spdlog::level::debug);
    setPattern("[%H:%M:%S %z] [%n] [%^---%L---%$] %v");
}

void ConsoleLogWriter::consoleMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";

    QString tMessage = "[ POSITION:{" + QString::fromUtf8(file) + ":" + QString::number(context.line) + "," + function +
            "} DETAIL:{" + QString::fromUtf8(localMsg.constData()) + "}]";

    QString tMessageType;
    switch (type) {
    case QtDebugMsg:
        tMessageType = "Debug";
        handleDebug(tMessage);
        break;
    case QtInfoMsg:
        tMessageType = "Info";
       handleInfo(tMessage);
        break;
    case QtWarningMsg:
        tMessageType = "Warning";
        handleWarning(tMessage);
        break;
    case QtCriticalMsg:// QtSystemMsg and QtCriticalMsg are same inspect QtMsgType
        tMessageType = "Critical";
        handleCritical(tMessage);
        break;
    case QtFatalMsg: //QtFatalMsg  redirec to trace because fatal log not found in spdlog
        tMessageType = "Fatal";
        handleTrace(tMessage);
        break;
    }

    fprintf(stderr, "%s: %s\n", tMessageType.toLocal8Bit().constData(), tMessage.toLocal8Bit().constData());
    fflush(stderr);
}
