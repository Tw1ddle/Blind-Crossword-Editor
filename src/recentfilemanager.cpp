#include "recentfilemanager.h"

#include <QSettings>
#include <QApplication>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "appsettings.h"

using namespace AppInfo;

RecentFileManager::RecentFileManager(Editor::MainWindow* window, Ui::MainWindow* ui, int maxFiles) :
    m_MaxFiles(maxFiles)
{
    Q_ASSERT(maxFiles >= 0);

    createActions(window, ui);
    updateActions();
}

void RecentFileManager::createActions(Editor::MainWindow* window, Ui::MainWindow* ui)
{
    // Allow the user to clear the recent files list
    connect(ui->actionClear_Recent_Files, SIGNAL(triggered()), this, SLOT(clearFiles()));

    // Create the recent file actions, hook them up to the UI and hide them
    for(int i = 0; i < m_MaxFiles; i++)
    {
        std::unique_ptr<QAction> action = std::unique_ptr<QAction>(new QAction(window));
        action->setVisible(false);
        m_RecentActions.push_back(std::move(action));
        connect(m_RecentActions[i].get(), SIGNAL(triggered()), window, SLOT(loadRecentCrossword()));
        ui->menuRecent_Files->addAction(m_RecentActions[i].get());
    }
}

// TODO Check for a bug that can occur - filepaths can be implementation/OS dependent e.g. separators
void RecentFileManager::addFile(const QString& filepath)
{
    QSettings settings;
    QStringList files = settings.value(SettingsKeys::recentCrosswordFiles).toStringList();

    files.removeAll(filepath); // Remove duplicates

    files.prepend(filepath);

    while(files.size() > m_MaxFiles)
    {
        files.removeLast();
    }

    settings.setValue(SettingsKeys::recentCrosswordFiles, files);

    updateActions();
}

void RecentFileManager::clearFiles()
{
    QSettings settings;

    settings.remove(SettingsKeys::recentCrosswordFiles);

    updateActions();
}

void RecentFileManager::updateActions()
{
    QSettings settings;
    QStringList files = settings.value(SettingsKeys::recentCrosswordFiles).toStringList();

    // Set up and show recently loaded files
    int numRecentFiles = qMin(files.size(), m_MaxFiles);
    for(int i = 0; i < numRecentFiles; i++)
    {
        QString text = files[i];
        m_RecentActions[i]->setText(text);
        m_RecentActions[i]->setData(files[i]);
        m_RecentActions[i]->setVisible(true);
    }
    // Hide the empty actions
    for (int j = numRecentFiles; j < m_MaxFiles; j++)
    {
        m_RecentActions[j]->setVisible(false);
    }
}
