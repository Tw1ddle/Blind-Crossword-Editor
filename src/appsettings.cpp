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

    m_Settings->sync();
}

AppSettings::~AppSettings()
{
    m_Settings->sync();
}

QString AppSettings::getDefaultSaveFilename()
{
    QString saveFilename = tr("untitled");

    return saveFilename;
}

int AppSettings::getMaxRecentCrosswordFiles() const
{
    bool ok = false;

    int max = m_Settings->value(maxRecentCrosswordFiles, Defaults::maxRecentCrosswordFiles).toInt(&ok);

    Q_ASSERT(ok);

    return max;
}

QStringList AppSettings::getRecentCrosswordFilepaths() const
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

QString AppSettings::getCrosswordLoadPath() const
{    
    auto path = m_Settings->value(crosswordLoadPath, Defaults::crosswordLoadPath).toString();

    Q_ASSERT(!path.isEmpty());

    auto fullpath = Utilities::getApplicationDirPath().append(path);

    QDir dir(fullpath);
    if(!dir.exists(fullpath))
    {
        fullpath = QString();
    }

    return fullpath;
}

QString AppSettings::getCrosswordSavePath() const
{
    auto path = m_Settings->value(crosswordSavePath, Defaults::crosswordSavePath).toString();

    Q_ASSERT(!path.isEmpty());

    // This works fine for Windows
    auto fullpath = Utilities::getApplicationDirPath().append(path);

    QDir dir(fullpath);
    if(!dir.exists(fullpath))
    {
        fullpath = QString();
    }

    // Other platforms might want different default paths...

    return fullpath;
}

void AppSettings::setCrosswordLoadPath(const QString& path)
{
    m_Settings->setValue(crosswordLoadPath, path);
}

void AppSettings::setCrosswordSavePath(const QString& path)
{
    m_Settings->setValue(crosswordSavePath, path);
}

QString AppSettings::getGridShapeFontName() const
{
    return m_Settings->value(gridShapeFontName, Defaults::gridShapeFontName).toString();
}

void AppSettings::setGridShapeFontName(const QString& name)
{
    m_Settings->setValue(gridShapeFontName, name);
}

int AppSettings::getGridShapeFontSize() const
{
    bool ok = false;

    int size = m_Settings->value(gridShapeFontSize, Defaults::gridShapeFontSize).toInt(&ok);

    Q_ASSERT(ok);

    return size;
}

void AppSettings::setGridShapeFontSize(int pointSize)
{
    m_Settings->setValue(gridShapeFontSize, pointSize);
}

}

}
