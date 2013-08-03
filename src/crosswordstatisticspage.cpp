#include "crosswordstatisticspage.h"
#include "ui_crosswordstatisticspage.h"

namespace Editor
{

CrosswordStatisticsPage::CrosswordStatisticsPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CrosswordStatisticsPage)
{
    ui->setupUi(this);
}

CrosswordStatisticsPage::~CrosswordStatisticsPage()
{
    delete ui;
}

}
