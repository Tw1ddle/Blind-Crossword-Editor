/*!
 * \section LICENSE
 *
 * Copyright 2013 Samuel Twidale
 *
 *
 *
 */

#include <QApplication>

#include <QStringList>
#include <QTranslator>
#include <QLibraryInfo>
#include <QtGlobal>

#include "mainwindow.h"
#include "appinfo.h"
#include "logginghandler.h"
#include "testrunner.h"

#ifdef QT_DEBUG
#include <QMessageBox>
#endif

int main(int argc, char *argv[])
{
    // Create the application
    QApplication app(argc, argv);

    // Run unit tests
    // Note that test data needs placing at appropriate paths for tests to run correctly
    #ifdef QT_DEBUG
    Tests::TestRunner testRunner;
    #endif

    // Set up message handler
    qInstallMessageHandler(Logging::debugConsoleOutputHandler);

    // Set up translations
    QTranslator translator;
    translator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    // Set app metadata
    app.setApplicationName(AppInfo::getAppName());
    app.setApplicationDisplayName(AppInfo::getAppName() + " " + AppInfo::getVersionNumber());
    app.setApplicationVersion(AppInfo::getVersionNumber());
    app.setOrganizationName(AppInfo::getOrganizationName()); // This must be set in order to use native QSettings storage

    // Get application arguments
    const QStringList arguments = app.arguments();

    // Debug - show each argument in a QMessageBox
    /*
    #ifdef QT_DEBUG
    for (int i = 0; i < arguments.size(); i++)
    {
        QMessageBox box;
        box.setText(arguments[i]);
        box.exec();
    }
    #endif
    */

    Editor::MainWindow mainWindow;

    // Pass arguments to main window for handling
    for (int i = 1; i < arguments.size(); i++)
    {
        mainWindow.handleArgument(arguments[i]);
    }

    mainWindow.show();

    return app.exec();
}
