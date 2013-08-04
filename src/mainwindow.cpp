#include "mainwindow.h"

#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QUrl>
#include <QMimeData>

#include <memory>

#include "ui_mainwindow.h"
#include "recentfilemanager.h"
#include "appsettings.h"
#include "utilities.h"
#include "aboutpage.h"
#include "gridview.h"
#include "appinfo.h"

using namespace Editor;
using namespace Crossword;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_Ui(std::unique_ptr<Ui::MainWindow>(new Ui::MainWindow)),
    m_Crossword(std::unique_ptr<CrosswordBase>(new CrosswordBase))
{
    // Set window icon
    setWindowIcon(QIcon(":/icons/icon.ico"));

    m_Ui->setupUi(this);

    // Set max number of recent files
    QSettings settings;
    bool ok;
    const int maxRecentFiles = settings.value(AppInfo::SettingsKeys::maxRecentCrosswordFiles, 10).toInt(&ok);
    Q_ASSERT(ok);

    m_RecentFiles = std::unique_ptr<AppInfo::RecentFileManager>(new AppInfo::RecentFileManager(this, m_Ui.get(), maxRecentFiles));

    // Capture drag-and-drop events etc
    installEventFilter(this);

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

    // Bring up a dialog with crossword templates

    m_Crossword->resetState();
}

void MainWindow::loadCrosswordDialog()
{
    // Construct a name filter for supported formats
    QStringList formats = m_FormatSupport.getSupportedLoadingExtensions();
    QString nameFilter;
    nameFilter.append(tr("Crossword files"));

    nameFilter.append(" (");
    for(auto format : formats)
    {
        nameFilter.append("*.").append(format).append(" ");
    }
    nameFilter.append(")");

    QString filepath = QFileDialog::getOpenFileName(this, tr("Open Crossword File"), QString(), nameFilter);
    if(!filepath.isNull())
    {
        // Convert the file path to use native directory separators
        // This gives consistency in directions of slashes e.g. on recent file list
        QString nativeFilepath = QDir::toNativeSeparators(filepath);

        loadCrossword(nativeFilepath);
    }
}

void MainWindow::loadRecentCrossword()
{
    const QAction* action = qobject_cast<QAction*>(sender());
    Q_ASSERT(action);
    Q_ASSERT(!action->data().toString().isEmpty());

    if(action)
    {
        QString filepath = action->data().toString();

        bool success = loadCrossword(filepath);

        if(!success)
        {
            m_RecentFiles->removeFile(filepath);
        }
    }
}

void MainWindow::dropEvent(QDropEvent* ev)
{
    QList<QUrl> urls = ev->mimeData()->urls();

    for(auto url : urls)
    {
        QString filepath = url.toLocalFile();
        QString nativeFilepath = QDir::toNativeSeparators(filepath);

        if(!filepath.isEmpty())
        {
            loadCrossword(nativeFilepath);
        }
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent* ev)
{
    ev->accept();
}

bool MainWindow::loadCrossword(const QString& filepath)
{
    auto newCrossword = loadCrosswordHelper(filepath);
    if(newCrossword == nullptr)
    {
        return false;
    }

    // Loading successful so do the setup
    m_Crossword.swap(newCrossword);
    m_RecentFiles->addFile(filepath);
    m_Crossword->setScene(m_Ui->graphicsView);

    return true;
}

// Helper method
// Returns nullptr on failure
std::unique_ptr<CrosswordBase> MainWindow::loadCrosswordHelper(const QString& filepath)
{
    // Check the file actually exists
    bool exists = Utilities::existsFile(filepath);

    if(!exists)
    {
        QMessageBox::information(this, tr("Could not find file"), tr("Could not find file: %1").arg(filepath));
        return nullptr;
    }

    auto crossword = std::unique_ptr<CrosswordBase>(new CrosswordBase());
    auto loader = m_FormatSupport.locateLoader(filepath);

    if(!loader)
    {
        // It has the wrong extension
        QMessageBox::information(this, tr("Unrecognized file"), tr("Could not recognize file: %1").arg(filepath));
        return nullptr;
    }

    bool success = loader->load(filepath, crossword->getState());

    if(!success)
    {
        // The loader failed
        QMessageBox::information(this, tr("Load failed"), tr("Failed to load crossword file: %1").arg(filepath));
        return nullptr;
    }

    // Internal sanity checks
    bool consistent = m_Crossword->isValid();

    if(!consistent)
    {
        QMessageBox::information(this, tr("Inconsistent file"), tr("File loaded with errors"));
    }

    return crossword;
}

void MainWindow::saveCrosswordDialog()
{
    // TODO Set a name filter for all supported formats
}

void MainWindow::saveCrossword()
{
    // Open save box, make the user choose the format and location therein
}

// Drag-and-drops
void MainWindow::loadFile(const QString& filepath)
{
    bool isSupportedCrosswordFormat = m_FormatSupport.isLoaderSupported(filepath);

    if(isSupportedCrosswordFormat)
    {
        loadCrossword(filepath);
    }

    // Different sorts of files go here (dictionaries, clue lists...?)
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

void MainWindow::showHomepage()
{
    bool success = Utilities::openUrl(AppInfo::getHomepage());

    Q_ASSERT(success);
}

void MainWindow::showAbout()
{
    AppInfo::AboutPage aboutPage;

    aboutPage.exec();
}

// Exiting the application

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    Q_UNUSED(object);

    // If more dragging and dropping is done elsewhere in the application later in development, then refine
    // the filter by specifying the widgets we want the file drop to work on
    if(event->type() == QEvent::DragEnter)
    {
        dragEnterEvent(static_cast<QDragEnterEvent*>(event));

        return true;
    }
    if(event->type() == QEvent::Drop)
    {
        dropEvent(static_cast<QDropEvent*>(event));

        return true;
    }

    return false;
}
