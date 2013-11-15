#include "newcrosswordcluepage.h"

#include "ui_newcrosswordcluepage.h"
#include "formatscommon.h"

namespace Editor
{

NewCrosswordCluePage::NewCrosswordCluePage(const Crossword::CrosswordState::ClueState& clueState, const std::vector<Grid::GridShape*> gridShapes, QWidget* parent) :
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
    // Coordinates and clue text
    QString coordinates;
    QString text;
    for(auto shape : m_GridShapes)
    {
        QString coordinate = VectorMath::toString<VectorMath::Vec3i>(shape->getItem().getCoordinate());
        coordinates.append(coordinate);
        coordinate.append("|");

        QString letter = shape->getItem().getText();
        text.append(letter);
    }

    ui->gridText->setText(text);

    ui->clueCoordinatesText->setText(coordinates);
    ui->clueDirectionText->setText("Across");
}

}
