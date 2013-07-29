#include "mainwindow.h"

#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QFileDialog>
#include <memory>

#include "ui_mainwindow.h"
#include "recentfilemanager.h"

using namespace Editor;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), m_Ui(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow))
{
    // Set window icon
    setWindowIcon(QIcon(":/icons/icon.ico"));

    m_Ui->setupUi(this);

    QSettings settings;
    bool ok;
    const int maxRecentFiles = settings.value(AppInfo::SettingsKeys::maxRecentCrosswordFiles, 10).toInt(&ok);
    Q_ASSERT(ok);

    m_RecentFiles = std::unique_ptr<AppInfo::RecentFileManager>(new AppInfo::RecentFileManager(this, m_Ui.get(), maxRecentFiles));

    connect(m_Ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadCrosswordDialog()));
}

MainWindow::~MainWindow()
{
    // Destructor required due to unique_ptr members needing it for destructors that throw
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
    // TODO confirmations here

    m_Crossword.resetState();
}

void MainWindow::loadRecentCrossword()
{
    const QAction* action = qobject_cast<QAction*>(sender());
    Q_ASSERT(action);

    if(action)
    {
        loadCrossword(action->data().toString());
    }
}

void MainWindow::loadCrosswordDialog()
{
    // TODO Set a name filter for supported formats
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Crossword File"));

    if(!filePath.isNull())
    {
        // Convert the file path to use native directory separators
        // This gives consistency in directions of slashes e.g. on recent file list
        QString nativeFilePath = QDir::toNativeSeparators(filePath);

        loadCrossword(nativeFilePath);
    }
}

void MainWindow::saveCrosswordDialog()
{
    // TODO Set a name filter for all supported formats
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
        else
        {
            // Only add the file to the recent files list if it loads successfully
            m_RecentFiles->addFile(filepath);
        }
    }
    else
    {
        // It has the wrong extension
        QMessageBox::information(this, tr("Invalid file"), tr("Could not recognize file").arg(filepath));
    }

    Q_ASSERT(m_Crossword.isValid());
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
