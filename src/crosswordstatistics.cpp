#include "crosswordstatistics.h"

#include "formatscommon.h"
#include "appsettings.h"

namespace Editor
{

// TODO solution grid or puzzle grid??
QString numLettersInGrid(const Crossword::CrosswordState& state)
{
    auto& grid = state.m_GridState.m_Grid;

    int numLetters = 0;

    for(auto& item : grid)
    {
        QString itemText = std::get<Crossword::CrosswordState::GridState::SOLUTION>(item).getText();

        numLetters += itemText.size();
    }

    return QString::number(numLetters);
}

QString numItemsInGrid(const Crossword::CrosswordState& state)
{
    auto& dimensions = state.m_GridState.m_Dimensions;

    int numItems = dimensions.x() * dimensions.y() * dimensions.z();

    return QString::number(numItems);
}

// TODO solution grid or puzzle grid??
QString numEmptiesInGrid(const Crossword::CrosswordState& state)
{
    auto& grid = state.m_GridState.m_Grid;

    int numEmpties = 0;

    for(auto& item : grid)
    {
        QString itemText = std::get<Crossword::CrosswordState::GridState::SOLUTION>(item).getText();

        if(itemText.size() == 0)
        {
            numEmpties++;
        }
    }

    return QString::number(numEmpties);
}

QString numClues(const Crossword::CrosswordState& state)
{
    auto size = state.m_ClueState.m_Clues.size();

    return QString::number(size);
}

QString numCluesForDirection(const Crossword::CrosswordState& state, const QString& direction)
{
    auto directions = Crossword::Formats::Common::getDirections();

    // Bad direction
    if(!directions.contains(direction))
    {
        return "0";
    }

    auto& clues = state.m_ClueState.m_Clues;

    int numClues = 0;
    for(auto& clue : clues)
    {
        if(clue.getDirection() == direction)
        {
            numClues++;
        }
    }

    return QString::number(numClues);
}

}
