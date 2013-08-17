#include "newcrosswordpage.h"
#include "ui_newcrosswordpage.h"

namespace Editor
{

NewCrosswordPage::NewCrosswordPage(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NewCrosswordPage)
{
    ui->setupUi(this);
}


NewCrosswordPage::~NewCrosswordPage()
{
    delete ui;
}

void NewCrosswordPage::setupContent()
{
    
}

}
