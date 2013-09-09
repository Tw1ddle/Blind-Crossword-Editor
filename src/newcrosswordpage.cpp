#include "newcrosswordpage.h"
#include "ui_newcrosswordpage.h"

namespace Editor
{

NewCrosswordPage::NewCrosswordPage(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NewCrosswordPage)
{
    ui->setupUi(this);

    setupContent();
}


NewCrosswordPage::~NewCrosswordPage()
{
    delete ui;
}

void NewCrosswordPage::setupContent()
{
}

void NewCrosswordPage::quickSelected()
{
}

void NewCrosswordPage::rectangularSelected()
{
}

void NewCrosswordPage::combinationLockSelected()
{
}

void NewCrosswordPage::barredSelected()
{
}

}
