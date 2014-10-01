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
    auto numberText = ui->clueNumberComboBox->itemData(ui->clueNumberComboBox->currentIndex()).toString();

    auto clueText = ui->clueGuessText->text();

    auto guessText = ui->clueGuessText->text();

    auto componentLengthsText = ui->clueComponentsLengthText->text();

    QString solutionText;
    std::vector<VectorMath::Vec3i> letterPositions;

    for(int i = 0; i < (int)m_GridShapes.size(); i++)
    {
        solutionText.append(m_GridShapes.at(i)->getItem().getText());
        letterPositions.push_back(m_GridShapes.at(i)->getItem().getCoordinate());
    }

    auto direction = Crossword::Formats::getDirection(letterPositions);
    auto directions = Crossword::Formats::Common::getDirections();
    QString directionText = directions.key(direction);

    return Crossword::CrosswordClue(numberText,
                                    guessText,
                                    solutionText,
                                    clueText,
                                    directionText,
                                    componentLengthsText,
                                    letterPositions);
}

void NewCrosswordCluePage::setupContent()
{
    QString solutionText;
    std::vector<VectorMath::Vec3i> letterPositions;

    for(int i = 0; i < (int)m_GridShapes.size(); i++)
    {
        solutionText.append(m_GridShapes.at(i)->getItem().getText());
        letterPositions.push_back(m_GridShapes.at(i)->getItem().getCoordinate());
    }

    auto direction = Crossword::Formats::getDirection(letterPositions);
    auto directions = Crossword::Formats::Common::getDirections();
    QString directionText = directions.key(direction);

    ui->gridText->setText(solutionText);
    ui->clueDirectionText->setText(directionText);
}

}
