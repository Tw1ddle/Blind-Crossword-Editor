#include "recentfilemanager.h"

#include <QSettings>
#include <QApplication>
#include <assert.h>

#include "mainwindow.h"

using namespace AppInfo;

RecentFileManager::RecentFileManager(Editor::MainWindow* window, Ui::MainWindow* ui, int maxFiles) :
    m_MaxFiles(maxFiles)
{
    assert(maxFiles >= 0);

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
        ui->menuOpen->addAction(m_RecentActions[i].get());
    }
}

void RecentFileManager::addFile(const QString& filepath)
{
    QSettings settings;

    QStringList files = settings.value("recentFileList").toStringList();

    files.removeAll(filepath);
    files.prepend(filepath);

    while(files.size() > m_MaxFiles)
    {
        files.removeLast();
    }

    settings.setValue("recentFileList", files);

    updateActions();
}

void RecentFileManager::clearFiles()
{
    QSettings settings;

    settings.setValue("recentFileList", QStringList());
    settings.sync();

    updateActions();
}

void RecentFileManager::updateActions()
{
    QSettings settings;

    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), m_MaxFiles);

    for(int i = 0; i < numRecentFiles; i++)
    {
        QString text = tr("&%1 %2").arg(i + 1).arg(files[i]);
        m_RecentActions[i]->setText(text);
        m_RecentActions[i]->setData(files[i]);
        m_RecentActions[i]->setVisible(true);
    }
    for (int j = numRecentFiles; j < m_MaxFiles; j++)
    {
        m_RecentActions[j]->setVisible(false);
    }
}
