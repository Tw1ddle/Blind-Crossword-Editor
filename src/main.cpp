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
#include <QDebug>

#include "mainwindow.h"
#include "appinfo.h"
#include "logginghandler.h"
#include "testrunner.h"

#ifdef QT_DEBUG
#include <QMessageBox>
#endif

namespace Editor
{

class CrosswordApplication : public QApplication
{
public:
    CrosswordApplication(int& argc, char *argv[]) : QApplication(argc, argv)
    {
    }

    // Log all thrown exceptions
    virtual bool notify(QObject* receiver, QEvent* event)
    {
        try
        {
            return QApplication::notify(receiver, event);
        }
        catch(std::exception& e)
        {
            qDebug() << "Exception thrown: " << e.what();
        }
        catch(...)
        {
            qDebug() << "Unknown exception thrown";
        }

        return false;
    }
};

}

int main(int argc, char *argv[])
{
    // Create the application
    Editor::CrosswordApplication app(argc, argv);

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

    // Print the arguments
    #ifdef QT_DEBUG
    for(int i = 0; i < arguments.size(); i++)
    {
        qDebug() << qPrintable(QString("Invocation argument %1: %2 \n").arg(QString::number(i), arguments.at(i)));
    }
    #endif

    Editor::MainWindow mainWindow;

    // Pass arguments to main window for handling
    for (int i = 1; i < arguments.size(); i++)
    {
        mainWindow.handleArgument(arguments[i]);
    }

    mainWindow.show();

    app.exec();
}
