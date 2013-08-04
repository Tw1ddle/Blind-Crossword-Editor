#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

public slots:
    // On file menu, but may also be called if an associated puzzle is double clicked
    bool loadCrossword(const QString& filepath);
    // Open from a "recent files" submenu
    void loadRecentCrossword();

protected:
    // Drag-and-drop
    bool eventFilter(QObject* object, QEvent* event);
    void dropEvent(QDropEvent* ev);
    void dragEnterEvent(QDragEnterEvent* ev);

    // Exit
    void closeEvent(QCloseEvent* event);

private:
    // Try to load any old file; helper for drag-and-drops
    void loadFile(const QString& filepath);

    // Helper methods for loading crosswords
    std::unique_ptr<Crossword::CrosswordBase> loadCrosswordHelper(const QString& filepath);
    std::unique_ptr<Crossword::CrosswordBase> loadRecentCrosswordHelper();
    
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
    void showHomepage();
    void showAbout();

private:
    std::unique_ptr<Ui::MainWindow> m_Ui;
    std::unique_ptr<AppInfo::RecentFileManager> m_RecentFiles; // To set up and update recently opened file paths

    std::unique_ptr<Crossword::CrosswordBase> m_Crossword;
    Crossword::Formats::CrosswordFormatSupportLocator m_FormatSupport;
};

}

#endif // MAINWINDOW_H
