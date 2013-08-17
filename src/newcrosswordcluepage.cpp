#include "newcrosswordcluepage.h"

#include "ui_newcrosswordcluepage.h"

namespace Editor
{

NewCrosswordCluePage::NewCrosswordCluePage(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NewCrosswordCluePage)
{
    ui->setupUi(this);
}

NewCrosswordCluePage::~NewCrosswordCluePage()
{
    delete ui;
}

}
