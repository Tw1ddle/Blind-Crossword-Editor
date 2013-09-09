#include "newcrosswordcluepage.h"

#include "ui_newcrosswordcluepage.h"
#include "formatscommon.h"

namespace Editor
{

NewCrosswordCluePage::NewCrosswordCluePage(const Crossword::CrosswordState::ClueState& clueState, const QList<Grid::GridShape*> gridShapes, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::NewCrosswordCluePage),
    m_ClueState(clueState),
    m_GridShapes(gridShapes)
{
    ui->setupUi(this);

    setupContent();
}

NewCrosswordCluePage::~NewCrosswordCluePage()
{
    delete ui;
}

Crossword::CrosswordClue NewCrosswordCluePage::getClue()
{
    auto number = ui->clueNumberComboBox->itemData(ui->clueNumberComboBox->currentIndex());
    auto clueText = ui->clueTextLabel->text();

    std::vector<VectorMath::Vec3i> letterPositions;

    // TODO
    return Crossword::CrosswordClue("2", "", "", clueText, "direction", "", letterPositions);
}

void NewCrosswordCluePage::setupContent()
{
    // TODO

    ui->clueTextLineEdit->setText(tr("Clue text..."));
    ui->clueIdentifierText->setText("1");
    ui->clueCoordinatesText->setText("{ 1, 2, 3 }, { 2, 4, 5 }");
    ui->clueDirectionText->setText("Across");
}

}
