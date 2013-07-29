#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

#include <memory>

namespace AppInfo
{

namespace SettingsKeys
{
// Keys for use with QSettings - these need to be unique
// Don't make identical keys except for case
// Don't use slashes in names except for hierarchical keys
const QString recentCrosswordFiles = "recentcrosswordfiles";
const QString maxRecentCrosswordFiles = "maxrecentcrosswordfiles";

}

// Persistent platform-independent application settings
class AppSettings
{
public:
    AppSettings(); // Load settings on creation
    ~AppSettings(); // Save settings on destruction

    void loadSettings();
    void saveSettings();

private:
    std::unique_ptr<QSettings> m_Settings;
};

}

#endif // APPSETTINGS_H
