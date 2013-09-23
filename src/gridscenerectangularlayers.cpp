#include "gridscenerectangularlayers.h"

#include "gridscene.h"
#include "gridsquare.h"
#include "gridsceneundocommands.h"

#include <QKeyEvent>

namespace Grid
{

GridSceneRectangularLayers::GridSceneRectangularLayers(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) : GridScene3D(parent, crosswordState)
{
    m_TypingDirection = RIGHT;

    auto numGrids = getCrosswordInterface()->getGrid().m_Dimensions.z();

    for(int z = 0; z < numGrids; z++)
    {
        addGrid(z);
    }
}

void GridSceneRectangularLayers::addGrid(int gridNumber)
{
    Crossword::CrosswordState::GridState& gridModel = getCrosswordInterface()->getGrid();

    QGraphicsItemGroup* gridItem = new QGraphicsItemGroup();

    auto dimensions = gridModel.m_Dimensions;
    auto baseIndex = dimensions.x() * dimensions.y() * gridNumber; // Start of grid
    auto lastIndex = dimensions.x() * dimensions.y() * (gridNumber + 1); // End of grid

    for(int i = baseIndex; i < lastIndex; i++)
    {
        auto coordinate = std::get<Crossword::CrosswordState::GridState::ITEM>(gridModel.m_Grid.at(i)).getCoordinate();
        Crossword::CrosswordItem& letter = std::get<Crossword::CrosswordState::GridState::ITEM>(gridModel.m_Grid.at(i));

        // TODO get size setting
        Grid::GridSquare* square = new Grid::GridSquare(letter, 100, 100);
        // TODO get item spacing setting
        square->setPos(coordinate.x() * 100, coordinate.y() * 100 + gridNumber * 700);
        square->setParentItem(gridItem);

        addItem(square);

        addGridShape(square);
    }

    addItem(gridItem);
}

void GridSceneRectangularLayers::keyPressEvent(QKeyEvent* event)
{
    // Set the direction of typing (perspective of looking at 3D grids from the side)
    auto key = event->key();

    if(isNavigationKey(key))
    {
        switch (key)
        {
        case Qt::Key_Right:
            m_TypingDirection = RIGHT;
            break;
        case Qt::Key_Left:
            m_TypingDirection = LEFT;
            break;
        case Qt::Key_Up:
            m_TypingDirection = AWAY;
            break;
        case Qt::Key_Down:
            m_TypingDirection = TOWARDS;
            break;
        case Qt::Key_PageDown:
            m_TypingDirection = DOWN;
            break;
        case Qt::Key_PageUp:
            m_TypingDirection = UP;
            break;
        }
        selectNextGridShape();
    }

    GridScene3D::keyPressEvent(event);

    event->accept();
}

void GridSceneRectangularLayers::keyReleaseEvent(QKeyEvent* event)
{
    GridScene3D::keyReleaseEvent(event);
}

bool GridSceneRectangularLayers::isNavigationKey(int keyCode) const
{
    bool isNavigation = (keyCode == Qt::Key_Right ||
                         keyCode == Qt::Key_Left ||
                         keyCode == Qt::Key_Up ||
                         keyCode == Qt::Key_Down ||
                         keyCode == Qt::Key_PageDown ||
                         keyCode == Qt::Key_PageUp);

    return isNavigation;
}

bool GridSceneRectangularLayers::selectNextGridShape()
{
    auto shapes = getSelectedGridShapes();

    if(shapes.size() != 1)
    {
        return false;
    }

    auto current = shapes.at(0)->getItem().getCoordinate();
    VectorMath::Vec3i next(0, 0, 0);
    auto state = getCrosswordInterface();

    switch(m_TypingDirection)
    {
    case RIGHT:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::ACROSS, current);
        break;
    case LEFT:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::BACKWARDS, current);
        break;
    case AWAY:
        // Since (0,0) is at the upper left of a grid, pressing "towards" the front of the puzzle actually goes "down" the page
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::TOWARDS, current);
        break;
    case TOWARDS:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::AWAY, current);
        break;
    case UP:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::UP, current);
        break;
    case DOWN:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::DOWN, current);
        break;
    }

    auto shape = getGridShapeForCoordinate(next);

    beginCommandMacro("Select next grid shape");
    addCommand(new ClearSelectionCommand(selectedItems()));
    addCommand(new SelectItemCommand(shape));
    endCommandMacro();

    return true;
}

GridShape* GridSceneRectangularLayers::getGridShapeForCoordinate(VectorMath::Vec3i coordinate)
{
    auto gridX = getCrosswordInterface()->getGridDimensions().x();
    auto gridY = getCrosswordInterface()->getGridDimensions().y();

    return getGridShapes().at(coordinate.x() + (coordinate.y() * gridX) + (coordinate.z() * gridX * gridY));
}

}
