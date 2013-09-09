#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QString>
#include <QStringList>
#include <QDir>

#include <memory>

class QSettings;

namespace Editor
{

namespace Preferences
{

// Keys for use with QSettings - these need to be unique
// Don't make identical keys except for case
// Don't use slashes in names except for hierarchical keys
namespace
{
const QString recentCrosswordFiles = "recentcrosswordfiles";
const QString maxRecentCrosswordFiles = "maxrecentcrosswordfiles";

const QString crosswordLoadPath = "crosswordloadpath";
const QString crosswordSavePath = "crosswordsavepath";

}

namespace Defaults
{
const QString crosswordLoadPath = "/Crosswords/";
const QString crosswordSavePath = "/Crosswords/";

const int maxRecentCrosswordFiles = 10;
}

// Persistent platform-independent application settings

// TODO make const correct
class AppSettings
{
public:
    AppSettings();
    ~AppSettings();

    static QString getDefaultSaveFilename();

    // Recent crossword files
    int getMaxRecentCrosswordFiles();
    void setMaxRecentCrosswordFiles(int max);
    QStringList getRecentCrosswordFilepaths();
    void setRecentCrosswordFilepaths(const QStringList& paths);
    void clearRecentCrosswordFilepaths();

    // Default load/save folders
    QString getCrosswordLoadPath();
    QString getCrosswordSavePath();

    void setCrosswordLoadPath(const QString& path);
    void setCrosswordSavePath(const QString& path);

private:
    // On settings object creation and destruction
    void loadSettings();
    void saveSettings();

    std::unique_ptr<QSettings> m_Settings;
};

}
}

#endif // APPSETTINGS_H
