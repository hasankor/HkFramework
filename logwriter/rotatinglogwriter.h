#ifndef ROTATINGLOGWRITER_H
#define ROTATINGLOGWRITER_H

#include "logwriterbase.h"

class RotatingLogWriter : public LogWriterBase
{
public:
    RotatingLogWriter(QString pLoggerName, QString pFileName, uint32_t pMaxMBSize, uint8_t pMaxFiles, QObject *parent);

private:
    const static int ONE_MB = 1048576;
};

#endif // ROTATINGLOGWRITER_H
