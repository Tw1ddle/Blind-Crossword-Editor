#include "mainwindow.h"

#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <memory>

#include "assert.h"

using namespace Editor;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_Ui(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow))
{
    // Set window icon
    setWindowIcon(QIcon(":/icons/icon.ico"));

    m_Ui->setupUi(this);

    const int maxRecentFiles = 10;
    m_RecentFiles = std::unique_ptr<AppInfo::RecentFileManager>(new AppInfo::RecentFileManager(this, m_Ui.get(), maxRecentFiles));
}

// Invocation arguments

void MainWindow::handleArgument(const QString& arg)
{
    // Attempts to load the first (and only the first) file with a valid crossword extension (if any)
    // If the arguments end with a file format extension, try to load it
    if(m_FormatSupport.isLoaderSupported(arg))
    {
        loadCrossword(arg);
    }
    #ifdef QT_DEBUG
    if(!m_FormatSupport.isLoaderSupported(arg))
    {
        QMessageBox::information(this, tr("Unrecognized Argument"), tr("Could not parse argument: %1").arg(arg));
    }
    #endif

    // More argument handling could go here
}

// File menu implementations

void MainWindow::newCrossword()
{

}

void MainWindow::loadRecentCrossword()
{
    const QAction* action = qobject_cast<QAction*>(sender());
    assert(action);

    if(action)
    {
        loadCrossword(action->data().toString());
    }
}

void MainWindow::loadCrossword(const QString& filepath)
{
    auto loader = m_FormatSupport.locateLoader(filepath);

    if(loader)
    {
        bool success = loader->load(filepath, m_Crossword.getState());

        if(!success)
        {
            // The loader failed
            QMessageBox::information(this, tr("Load failed"), tr("Failed to load crossword file: %1").arg(filepath));
        }
    }
    else
    {
        // It has the wrong extension
        QMessageBox::information(this, tr("Invalid file"), tr("Could not recognize file").arg(filepath));
    }

    Q_ASSERT(m_Crossword.isValid());

    // TODO If the file doesn't load successfully we shouldn't add it to the recent files list
    m_RecentFiles->addFile(filepath);
}

void MainWindow::saveCrossword()
{
    // Open save box, make the user choose the format and location therein
}

void MainWindow::printCrossword()
{

}

void MainWindow::emailCrossword()
{

}

void MainWindow::showCrosswordProperties()
{
    // Open a messagebox with the properties?
}

void MainWindow::showQuitConfirmation()
{
    // Show message box with warning (you need to save your stuff?) and option to quit or not
}

// Options menu implementations

void MainWindow::fitGridsInView()
{
    // Call method on graphics scene/view to do this
}

// About menu implementations

void MainWindow::showHelp()
{

}

void MainWindow::showAbout()
{

}

void MainWindow::showLicense()
{

}

// Exiting the application

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
}
