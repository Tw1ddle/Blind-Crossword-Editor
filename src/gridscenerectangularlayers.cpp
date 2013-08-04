#include "gridscenerectangularlayers.h"

#include "gridscene.h"
#include "gridsquare.h"

#include <QGraphicsSimpleTextItem>

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

    // Add a tag indicating the grid #
    // TODO fix the grouping code - probably doing something wrong or unnecessary here
    QString gridNumberString = QString::number(gridNumber);
    QString gridStringTag = tr("Grid %1").arg(gridNumberString);
    QGraphicsSimpleTextItem* gridTag = new QGraphicsSimpleTextItem(gridStringTag);
    auto coordinate = gridModel.m_Grid.at(baseIndex).first;

    // TODO get item spacing and grid tag offset
    gridTag->setPos(coordinate.x() * 100 - 30, coordinate.y() * 100 + gridNumber * 700);
    gridTag->setParentItem(gridItem);
    addItem(gridTag);

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
