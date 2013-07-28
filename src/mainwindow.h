#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "appsettings.h"
#include "crosswordbase.h"
#include "crosswordformatsupportlocator.h"

namespace Ui
{
    class MainWindow;
}

namespace AppInfo
{
    class RecentFileManager;
}

namespace Editor
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    void handleArgument(const QString& arg); // Handle argument, probably passed by the main method

protected:
    // Exit
    void closeEvent(QCloseEvent* event);

private:

public slots:
    // On file menu, but may also be called if an associated puzzle is double clicked
    void loadCrossword(const QString& filepath);
    // Open from a "recent files" submenu
    void loadRecentCrossword();
    
private slots:
    // File menu
    void loadCrosswordDialog();
    void saveCrosswordDialog();

    void newCrossword();
    void saveCrossword();
    void printCrossword();
    void emailCrossword();
    void showCrosswordProperties();
    void showQuitConfirmation();

    // Options
    void fitGridsInView();

    // About
    void showHelp();
    void showAbout();
    void showLicense();

signals:

private:
    std::unique_ptr<Ui::MainWindow> m_Ui;
    std::unique_ptr<AppInfo::RecentFileManager> m_RecentFiles; // To set up and update recently opened file paths
    AppInfo::AppSettings m_Settings;

    Crossword::Formats::CrosswordFormatSupportLocator m_FormatSupport;

    Crossword::CrosswordBase m_Crossword;
};

}

#endif // MAINWINDOW_H
