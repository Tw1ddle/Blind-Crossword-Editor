/*!
 * \section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 */

#include <QApplication>

#include <QStringList>
#include <QTranslator>
#include <QLibraryInfo>

#include "mainwindow.h"
#include "appinfo.h"

#ifdef QT_DEBUG
#include <QMessageBox>
#endif

int main(int argc, char *argv[])
{
    // Create the application
    QApplication app(argc, argv);

    // Set up translations
    QTranslator translator;
    translator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    // Set app metadata
    app.setApplicationName(AppInfo::getAppName());
    app.setApplicationDisplayName(AppInfo::getAppName());
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
