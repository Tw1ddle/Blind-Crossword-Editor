#include "preferencespage.h"
#include "ui_preferencespage.h"

#include "appsettings.h"

namespace Editor
{

namespace Preferences
{

PreferencesPage::PreferencesPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesPage)
{
    ui->setupUi(this);

    setupFolders();
}

PreferencesPage::~PreferencesPage()
{
    delete ui;
}

void PreferencesPage::setupFolders()
{
    AppSettings settings;

    ui->loadCrosswordFolderLineEdit->setText(settings.getCrosswordLoadPath());
    ui->saveCrosswordFolderLineEdit->setText(settings.getCrosswordSavePath());

    // TODO the crossword load path is relative to the application executable
}

}
}
