#include "gridscenerectangularlayers.h"

#include "gridscene.h"
#include "gridsquare.h"

namespace Grid
{

GridSceneRectangularLayers::GridSceneRectangularLayers(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) : GridScene3D(parent, crosswordState)
{
    auto grids = getCrosswordState()->getGrid().m_Dimensions.z();

    // For each grid
    for(int z = 0; z < grids; z++)
    {
        addGrid(z);
    }
}

void GridSceneRectangularLayers::addGrid(int gridNumber)
{
    const Crossword::CrosswordState::GridState& gridModel = getCrosswordState()->getGrid();

    QGraphicsItemGroup* gridItem = new QGraphicsItemGroup();

    auto dimensions = gridModel.m_Dimensions;
    auto baseIndex = dimensions.x() * dimensions.y() * gridNumber; // Start of grid
    auto lastIndex = dimensions.x() * dimensions.y() * (gridNumber + 1); // End of grid

    for(int i = baseIndex; i < lastIndex; i++)
    {
        auto coordinate = gridModel.m_Grid.at(i).first;
        const Crossword::CrosswordItem& letter = gridModel.m_Grid.at(i).second;

        // TODO get size setting
        Grid::GridSquare* square = new Grid::GridSquare(letter, 100, 100);

        // TODO get item spacing setting
        square->setPos(coordinate.x() * 100, coordinate.y() * 100 + gridNumber * 700);

        square->setParentItem(gridItem);
        addItem(square);
        gridItem->addToGroup(square);
    }

    addItem(gridItem);
}

}
