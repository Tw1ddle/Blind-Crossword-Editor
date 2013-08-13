#include "preferencespage.h"
#include "ui_preferencespage.h"

PreferencesPage::PreferencesPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesPage)
{
    ui->setupUi(this);
}

PreferencesPage::~PreferencesPage()
{
    delete ui;
}
