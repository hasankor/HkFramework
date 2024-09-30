#ifndef STATICCONSOLELOGWRITER_H
#define STATICCONSOLELOGWRITER_H

#include <QCoreApplication>

class StaticConsoleLogWriter
{
public:
    static void consoleMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    StaticConsoleLogWriter();
};

#endif // STATICCONSOLELOGWRITER_H
