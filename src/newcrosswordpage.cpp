#include "newcrosswordpage.h"
#include "ui_newcrosswordpage.h"

#include "crosswordtemplates.h"

namespace Editor
{

using namespace Crossword;

NewCrosswordPage::NewCrosswordPage(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NewCrosswordPage),
    m_NewCrossword(new CrosswordState())
{
    ui->setupUi(this);
}


NewCrosswordPage::~NewCrosswordPage()
{
    delete ui;
}

std::unique_ptr<CrosswordState> NewCrosswordPage::getState()
{
    return std::move(m_NewCrossword);
}

void NewCrosswordPage::quickSelected()
{
    std::unique_ptr<CrosswordState> quickCrossword = CrosswordTemplates::Empty::make2DGrid(7, 7);

    m_NewCrossword.swap(quickCrossword);

    accept();
}

void NewCrosswordPage::rectangularSelected()
{
    std::unique_ptr<CrosswordState> rectangularCrossword = CrosswordTemplates::Empty::make3DGrid(5, 5, 7);

    m_NewCrossword.swap(rectangularCrossword);

    accept();
}

void NewCrosswordPage::combinationLockSelected()
{
    std::unique_ptr<CrosswordState> combinationLockCrossword = CrosswordTemplates::Empty::make3DCombinationLock(5, 5, 5);

    m_NewCrossword.swap(combinationLockCrossword);

    accept();
}

void NewCrosswordPage::barredSelected()
{
    std::unique_ptr<CrosswordState> barredCrossword = CrosswordTemplates::Empty::make2DGrid(5, 5);

    m_NewCrossword.swap(barredCrossword);

    accept();
}

}
