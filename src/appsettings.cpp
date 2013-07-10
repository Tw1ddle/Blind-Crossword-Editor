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

}

void AppSettings::saveSettings()
{

}

}
