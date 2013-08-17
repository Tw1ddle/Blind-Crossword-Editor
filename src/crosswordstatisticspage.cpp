#include "crosswordstatisticspage.h"
#include "ui_crosswordstatisticspage.h"

#include "crosswordstatistics.h"
#include "crosswordstate.h"

namespace Editor
{

CrosswordStatisticsPage::CrosswordStatisticsPage(QWidget* parent, const Crossword::CrosswordState& state) :
    QDialog(parent),
    ui(new Ui::CrosswordStatisticsPage)
{
    ui->setupUi(this);
    setupContent(state);
}

CrosswordStatisticsPage::~CrosswordStatisticsPage()
{
    delete ui;
}

void CrosswordStatisticsPage::setupContent(const Crossword::CrosswordState& state)
{
    auto x = QString::number(state.m_GridState.m_Dimensions.x());
    auto y = QString::number(state.m_GridState.m_Dimensions.y());
    auto z = QString::number(state.m_GridState.m_Dimensions.z());

    ui->x->setText(x);
    ui->y->setText(y);
    ui->z->setText(z);

    ui->numSquares->setText(numItemsInGrid(state));
    ui->numLetters->setText(numLettersInGrid(state));
    ui->numEmpties->setText(numEmptiesInGrid(state));
}

}
