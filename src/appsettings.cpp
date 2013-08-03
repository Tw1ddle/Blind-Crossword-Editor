#include "appsettings.h"

#include "appinfo.h"

namespace AppInfo
{

AppSettings::AppSettings()
{
    // Read in settings from an ini file
    m_Settings = std::unique_ptr<QSettings>(new QSettings(AppInfo::getOrganizationName(), AppInfo::getAppName()));

    loadSettings();
}

AppSettings::~AppSettings()
{
    saveSettings();
}

void AppSettings::loadSettings()
{
    QSettings settings;

    Q_UNUSED(settings);

    // TODO
}

void AppSettings::saveSettings()
{
    QSettings settings;

    Q_UNUSED(settings);

    // TODO
}

}
