#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

#include <memory>

namespace AppInfo
{

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
