#ifndef APPINFO_H
#define APPINFO_H

#include <QString>

// Wrapper around informational macros defined in the qmake .pro
// Application name, version, organization etc
namespace AppInfo
{

inline QString getVersionNumber()
{
    return QString(APP_VERSION);
}

inline QString getAppName()
{
    return QString(APP_NAME);
}

inline QString getOrganizationName()
{
    return QT_TR_NOOP(QString(APP_ORGANIZATION));
}

inline QString getAppDescription()
{
    return QT_TR_NOOP(QString(APP_DESCRIPTION));
}

inline QString getCopyrightNotice()
{
    return QT_TR_NOOP(QString(APP_COPYRIGHT));
}

}

#endif // APPINFO_H
