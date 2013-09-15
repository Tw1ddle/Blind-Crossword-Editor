#ifndef APPINFO_H
#define APPINFO_H

#include <QString>
#include <QUrl>

// Settings that do not change between releases
// Also a wrapper around informational macros defined in the qmake .pro
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
    // TODO GPLv3 license text
    QString license = "This software is provided as-is, without any express or implied warranty.";

    return license;
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

inline QUrl getHomepage()
{
    return QUrl("http://www.calendarpuzzles.co.uk/");
}

inline QUrl getHelpWebsite()
{
    // TODO
    return QUrl("http://www.calendarpuzzles.co.uk/");
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
