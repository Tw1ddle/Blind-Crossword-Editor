#ifndef LOGGINGHANDLER_H
#define LOGGINGHANDLER_H

#include <QMessageLogContext>
#include <QString>

class QTextEdit;

namespace Logging
{

// Prints log messages to console
void debugConsoleOutputHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);

}

#endif // LOGGINGHANDLER_H
