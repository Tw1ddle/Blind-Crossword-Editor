#include "logginghandler.h"

#include <QTextStream>
#include <QTextEdit>

#include "appinfo.h"

#ifdef Q_OS_WIN32
#include "Windows.h"
#endif

namespace Logging
{

// Print debug information to the command line
void debugConsoleOutputHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QString output;

    output.append(AppInfo::getAppName()).append(" ").append(AppInfo::getVersionNumber()).append(" - ");

    // Print message type
    switch(type)
    {
    case QtDebugMsg: output.append(" DEBUG: "); break;
    case QtWarningMsg: output.append(" WARNING: "); break;
    case QtCriticalMsg: output.append(" CRITICAL: "); break;
    case QtFatalMsg: output.append(" FATAL: "); break;
    default:
        output.append(" UNKNOWN: "); break;
    }

    output.append(msg);

    output.append(". Line: ").append(context.line).append("\n");

    #ifdef Q_OS_WIN32
    OutputDebugString(reinterpret_cast<const wchar_t*>(output.utf16()));
    #endif
}

}
