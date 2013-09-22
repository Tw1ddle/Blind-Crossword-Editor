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
// Recent files
const QString recentCrosswordFiles = "recentcrosswordfiles";
const QString maxRecentCrosswordFiles = "maxrecentcrosswordfiles";

// Load/Save paths
const QString crosswordLoadPath = "crosswordloadpath";
const QString crosswordSavePath = "crosswordsavepath";

// Grid properties
const QString gridShapeFontName = "gridshapefontname";
const QString gridShapeFontSize = "gridshapefontsize";
}

namespace Defaults
{
// Recent files
const int maxRecentCrosswordFiles = 10;

// Load/Save paths
const QString crosswordLoadPath = "/Crosswords/";
const QString crosswordSavePath = "/Crosswords/";

// Grid properties
const QString gridShapeFontName = "Times";
const int gridShapeFontSize = 12;
}

// Persistent platform-independent application settings
class AppSettings : QObject
{
    Q_OBJECT
public:
    AppSettings();
    ~AppSettings();

    // Recent crossword files
    int getMaxRecentCrosswordFiles() const;
    void setMaxRecentCrosswordFiles(int max);
    QStringList getRecentCrosswordFilepaths() const;
    void setRecentCrosswordFilepaths(const QStringList& paths);
    void clearRecentCrosswordFilepaths();

    // Load/Save paths
    QString getCrosswordLoadPath() const;
    QString getCrosswordSavePath() const;
    void setCrosswordLoadPath(const QString& path);
    void setCrosswordSavePath(const QString& path);

    static QString getDefaultSaveFilename();

    // Grid properties
    QString getGridShapeFontName() const;
    void setGridShapeFontName(const QString& name);
    int getGridShapeFontSize() const;
    void setGridShapeFontSize(int pointSize);

private:
    std::unique_ptr<QSettings> m_Settings;
};

}
}

#endif // APPSETTINGS_H
