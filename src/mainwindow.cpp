#include "mainwindow.h"

#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QUrl>
#include <QMimeData>
#include <QDesktopServices>
#include <QAbstractButton>

#include <memory>

#include "ui_mainwindow.h"
#include "recentfilemanager.h"
#include "appsettings.h"
#include "utilities.h"
#include "gridview.h"
#include "appinfo.h"

#include "aboutpage.h"
#include "preferencespage.h"
#include "crosswordstatisticspage.h"
#include "newcrosswordpage.h"

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
    Preferences::AppSettings settings;
    const int maxRecentFiles = settings.getMaxRecentCrosswordFiles();

    m_RecentFiles = std::unique_ptr<Editor::RecentFileManager>(new Editor::RecentFileManager(this, m_Ui.get(), maxRecentFiles));

    // Capture drag-and-drop events etc
    installEventFilter(this);
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
    NewCrosswordPage newCrosswordPage(this);

    // TODO get a chosen template from this
    newCrosswordPage.exec();

    // m_Crossword->setState(newCrosswordPage.getState());
}

void MainWindow::loadCrosswordDialog()
{
    // Construct a name filter for supported formats
    QStringList formats = m_FormatSupport.getSupportedLoadingExtensions();
    QString nameFilter = Utilities::createNameFilter(tr("Crossword Files"), formats);

    // Attempt to get the default directory for looking for crosswords in
    Preferences::AppSettings settings;
    QString defaultDirectory = settings.getCrosswordLoadPath();
    QDir dir(defaultDirectory);
    if(!dir.exists(defaultDirectory))
    {
        defaultDirectory = QString();
    }

    QString filepath = QFileDialog::getOpenFileName(this, tr("Open Crossword File"), defaultDirectory, nameFilter);
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

    auto loader = m_FormatSupport.locateLoader(filepath);

    if(!loader)
    {
        // It has the wrong extension
        QMessageBox::information(this, tr("Unrecognized file"), tr("Could not recognize file: %1").arg(filepath));
        return nullptr;
    }

    auto crossword = std::unique_ptr<CrosswordBase>(new CrosswordBase());
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

bool MainWindow::saveCrosswordDialog()
{
    // TODO
    // If the puzzle has been saved under a file path already, then overwrite the file
    // Otherwise open a dialog with a default name and a list of formats to choose from

    // Attempt to use a default save directory
    Preferences::AppSettings settings;
    QString defaultDirectory = settings.getCrosswordSavePath();
    QDir dir(defaultDirectory);
    if(!dir.exists(defaultDirectory))
    {
        defaultDirectory = QString();
    }

    QString filepath = QFileDialog::getSaveFileName(this, tr("Save Crossword File"), defaultDirectory, QString());
    if(filepath.isNull())
    {
        return false;
    }

    QStringList formats = m_FormatSupport.getSupportedSavingExtensions();
    QString nameFilter = Utilities::createNameFilter(tr("Crossword Files"), formats);

    // Convert the file path to use native directory separators
    QString nativeFilepath = QDir::toNativeSeparators(filepath);

    bool success = saveCrossword(nativeFilepath);

    // After saving successfully, add the saved file to top of recent files list
    if(success)
    {
        m_RecentFiles->addFile(nativeFilepath);
    }

    return success;
}

bool MainWindow::saveCrossword(const QString& filepath)
{
    bool saveable = m_Crossword->isSaveable();

    if(!saveable)
    {
        QMessageBox::information(this, tr("Could not save"), tr("This crossword is in an inconsistent state and could not be saved"));
        return false;
    }

    auto saver = m_FormatSupport.locateSaver(filepath);

    if(!saver)
    {
        // It has the wrong extension
        QMessageBox::information(this, tr("Unrecognized file extension"), tr("Could not recognize file save type: %1").arg(filepath));
        return false;
    }

    bool success = saver->save(filepath, m_Crossword->getState());

    if(!success)
    {
        // The saver failed
        QMessageBox::information(this, tr("Save failed"), tr("Failed to save crossword file: %1").arg(filepath));
        return false;
    }

    Q_ASSERT(m_Crossword->isValid()); // This has no side effects

    return true;
}

// Save the currently open crossword
bool MainWindow::saveCurrentCrossword()
{
    if(m_Crossword->hasFilepath())
    {
        return saveCrossword(m_Crossword->getFilename());
    }
    else
    {
        return saveCrosswordDialog();
    }
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
    // TODO
}

void MainWindow::emailCrossword()
{
    // TODO
}

void MainWindow::showCrosswordProperties()
{
    Editor::CrosswordStatisticsPage crosswordStatisticsPage(this, m_Crossword->getState());

    crosswordStatisticsPage.exec();
}

// Edit menu implementations

void MainWindow::showPreferences()
{
    Editor::Preferences::PreferencesPage preferencesPage(this);

    preferencesPage.exec();
}

// View menu implementations

void MainWindow::fitGridsInView()
{
    // TODO
    // Call method on graphics scene/view to do this
}

// About menu implementations

void MainWindow::showHelp()
{
    // TODO
}

void MainWindow::showHomepage()
{
    bool success = Utilities::openUrl(AppInfo::getHomepage());

    if(!success)
    {
        QMessageBox::information(this,
                                 tr("Homepage Failed to Open"),
                                 tr("Failed to open web browser. Find us online at %1").
                                 arg(AppInfo::getHomepage().toString()));
    }
}

void MainWindow::showAbout()
{
    AppInfo::AboutPage aboutPage(this);

    aboutPage.exec();
}

void MainWindow::showSupportEmail()
{
    QString supportEmail;

    // TODO check that this works with Asian languages etc

    supportEmail += "mailto:sam@silver42.karoo.co.uk?subject=";
    supportEmail += tr("Support Email");
    supportEmail += "&body=";
    supportEmail += tr("Please send your support message");

    QDesktopServices::openUrl(QUrl(supportEmail));
}

// Exiting the application

bool MainWindow::showQuitConfirmation()
{
    QMessageBox msgBox(this);
    msgBox.setText(tr("Do you want to save your changes to %1?").arg(m_Crossword->getFilename()));
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.button(QMessageBox::Discard)->setText(tr("Don't Save"));
    msgBox.setDefaultButton(QMessageBox::Save);
    // TODO center the buttons on this messagebox
    // ...
    // TODO check this behaviour isn't buggy!

    auto save = msgBox.exec();

    if(QMessageBox::Yes == save)
    {
        saveCurrentCrossword();

        return true;
    }
    else if(QMessageBox::No == save)
    {
        return true;
    }
    else if(QMessageBox::Cancel == save)
    {
        return false;
    }

    return true;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if(showQuitConfirmation())
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

// Event interception

bool MainWindow::eventFilter(QObject* object, QEvent* event)
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
