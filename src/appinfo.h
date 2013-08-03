#ifndef APPINFO_H
#define APPINFO_H

#include <QString>

// Wrapper around informational macros defined in the qmake .pro
// Application name, version, organization etc
namespace AppInfo
{

// Name and app description

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

inline QString getLicenseText()
{
    return QT_TR_NOOP("TODO license goes here");
}

// Credits

inline QString getProgrammers()
{
    return QString("Samuel Twidale");
}

inline QString getTranslators()
{
    return QString("Samuel Twidale");
}

inline QString getArtists()
{
    return QString("Samuel Twidale");
}

// Build information

inline QString getVersionNumber()
{
    return QString(APP_VERSION);
}

inline QString getCompilerName()
{
    return QString(APP_COMPILER_NAME);
}

inline QString getQtVersion()
{
    return QString(QT_VERSION_STR);
}

}

#endif // APPINFO_H
