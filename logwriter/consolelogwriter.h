#ifndef CONSOLELOGWRITER_H
#define CONSOLELOGWRITER_H

#include "rotatinglogwriter.h"

class ConsoleLogWriter : public RotatingLogWriter
{
    Q_OBJECT
public:
    ConsoleLogWriter(QString pFileName, uint32_t pMaxMBSize, uint8_t pMaxFiles, QObject* parent = nullptr);

    void consoleMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);
};

#endif // CONSOLELOGWRITER_H
