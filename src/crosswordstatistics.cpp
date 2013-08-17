#include "crosswordstatistics.h"

namespace Editor
{

QString numLettersInGrid(const Crossword::CrosswordState& state)
{
    auto& grid = state.m_GridState.m_Grid;

    int numLetters = 0;

    for(auto& item : grid)
    {
        QString itemText = item.second.getText();

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

QString numEmptiesInGrid(const Crossword::CrosswordState& state)
{
    auto& grid = state.m_GridState.m_Grid;

    int numEmpties = 0;

    for(auto& item : grid)
    {
        QString itemText = item.second.getText();

        if(itemText.size() == 0)
        {
            numEmpties++;
        }
    }

    return QString::number(numEmpties);
}

}
