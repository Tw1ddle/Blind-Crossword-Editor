#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "appsettings.h"
#include "crosswordbase.h"
#include "crosswordformatsupportlocator.h"
#include "ui_mainwindow.h"

namespace Editor
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    void handleArgument(const QString& arg); // Handle argument, probably passed by the main method

private:

public slots:
    // On file menu, but may also be called if an associated puzzle is double clicked
    void loadCrossword(const QString& filepath);
    
private slots:
    // File menu
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

    AppInfo::AppSettings m_Settings;
    Crossword::Formats::CrosswordFormatSupportLocator m_FormatSupport;

    Crossword::CrosswordBase m_Crossword;
};

}

#endif // MAINWINDOW_H
