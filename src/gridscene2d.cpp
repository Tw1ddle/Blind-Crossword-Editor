#include "gridscene2d.h"

namespace Grid
{

GridScene2D::GridScene2D(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) : GridScene(parent, crosswordState)
{
    addGrid();
}

void GridScene2D::addGrid()
{
    Crossword::CrosswordState::GridState& gridModel = getCrosswordState()->getGrid();

    QGraphicsItemGroup* gridItem = new QGraphicsItemGroup();

    for(unsigned int i = 0; i < gridModel.m_Grid.size(); i++)
    {
        auto coordinate = gridModel.m_Grid.at(i).first;
        Crossword::CrosswordItem& letter = gridModel.m_Grid.at(i).second;

        // TODO get size setting
        Grid::GridSquare* square = new Grid::GridSquare(letter, 100, 100);

        // TODO get item spacing setting
        square->setPos(coordinate.x() * 100, coordinate.y() * 100);

        square->setParentItem(gridItem);
        addItem(square);
    }

    addItem(gridItem);
}

}
