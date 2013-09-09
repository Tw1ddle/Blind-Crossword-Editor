#include "appsettings.h"

#include "appinfo.h"
#include "utilities.h"

#include <QSettings>

namespace Editor
{

namespace Preferences
{

AppSettings::AppSettings()
{
    m_Settings = std::unique_ptr<QSettings>(new QSettings(AppInfo::getOrganizationName(), AppInfo::getAppName()));

    loadSettings();
}

AppSettings::~AppSettings()
{
    saveSettings();
}

void AppSettings::loadSettings()
{
    m_Settings->sync();
}

void AppSettings::saveSettings()
{
    m_Settings->sync();
}

QString AppSettings::getDefaultSaveFilename()
{
    // TODO make translatable
    QString saveFilename = "untitled";

    return saveFilename;
}

int AppSettings::getMaxRecentCrosswordFiles()
{
    bool ok = false;

    int max = m_Settings->value(maxRecentCrosswordFiles, Defaults::maxRecentCrosswordFiles).toInt(&ok);

    Q_ASSERT(ok);

    return max;
}

QStringList AppSettings::getRecentCrosswordFilepaths()
{
    auto paths = m_Settings->value(recentCrosswordFiles).toStringList();

    return paths;
}

void AppSettings::setRecentCrosswordFilepaths(const QStringList& paths)
{
    m_Settings->setValue(recentCrosswordFiles, paths);
}

void AppSettings::clearRecentCrosswordFilepaths()
{
    m_Settings->remove(recentCrosswordFiles);
}

QString AppSettings::getCrosswordLoadPath()
{    
    auto path = m_Settings->value(crosswordLoadPath, Defaults::crosswordLoadPath).toString();

    Q_ASSERT(!path.isEmpty());

    // TODO may need changing for other platforms
    return Utilities::getApplicationDirPath().append(path);
}

QString AppSettings::getCrosswordSavePath()
{
    auto path = m_Settings->value(crosswordSavePath, Defaults::crosswordSavePath).toString();

    Q_ASSERT(!path.isEmpty());

    // TODO may need changing for other platforms
    return Utilities::getApplicationDirPath().append(path);
}

void AppSettings::setCrosswordLoadPath(const QString& path)
{
    m_Settings->setValue(crosswordLoadPath, path);
}

void AppSettings::setCrosswordSavePath(const QString& path)
{
    m_Settings->setValue(crosswordSavePath, path);
}

}

}
