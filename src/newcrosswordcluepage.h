#ifndef NEWCROSSWORDCLUEPAGE_H
#define NEWCROSSWORDCLUEPAGE_H

#include <QDialog>

#include "crosswordclue.h"
#include "crosswordstate.h"
#include "gridshape.h"

namespace Ui
{
    class NewCrosswordCluePage;
}

namespace Editor
{

class NewCrosswordCluePage : public QDialog
{
    Q_OBJECT
public:
    explicit NewCrosswordCluePage(const Crossword::CrosswordState::ClueState& clueState, const std::vector<Grid::GridShape*> gridShapes, QWidget* parent = 0);
    ~NewCrosswordCluePage();

    // Get the clue specified by the user
    Crossword::CrosswordClue getClue();

private:
    Ui::NewCrosswordCluePage* ui;

    void setupContent();

    const Crossword::CrosswordState::ClueState& m_ClueState;
    const std::vector<Grid::GridShape*> m_GridShapes;
};

}

#endif // NEWCROSSWORDCLUEPAGE_H
