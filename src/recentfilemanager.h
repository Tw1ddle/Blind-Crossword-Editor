#ifndef RECENTFILEMANAGER_H
#define RECENTFILEMANAGER_H

#include <QObject>
#include <QString>
#include <QAction>
#include <memory>

namespace Ui
{
    class MainWindow;
}

namespace Editor
{
    class MainWindow;
}

namespace AppInfo
{

// Models "recently opened file list" functionality for crossword puzzle files
class RecentFileManager : public QObject
{
    Q_OBJECT
public:
    RecentFileManager(Editor::MainWindow* window, Ui::MainWindow* ui, int maxFiles);
    
    void addFile(const QString& filepath); // Parameters are the actual file path and then the name that is displayed to the user

public slots:
    void updateActions();

private slots:
    void clearFiles();

private:
    void createActions(Editor::MainWindow* window, Ui::MainWindow* ui);

    std::vector<std::unique_ptr<QAction>> m_RecentActions;
    int m_MaxFiles; // Maximum number of recent files to remember
};

}

#endif // RECENTFILEMANAGER_H
