#include "gridscenecombinationlock.h"

#include "gridscene.h"
#include "gridsquare.h"
#include "gridsceneundocommands.h"

#include <QKeyEvent>

namespace Grid
{

GridSceneCombinationLock::GridSceneCombinationLock(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) : GridScene3D(parent, crosswordState)
{
    m_TypingDirection = CLOCKWISE;

    auto numGrids = getCrosswordInterface()->getGrid().m_Dimensions.z();

    for(int z = 0; z < numGrids; z++)
    {
        addGrid(z);
    }
}

void GridSceneCombinationLock::addGrid(int gridNumber)
{
    Q_UNUSED(gridNumber);
    // TODO
}

void GridSceneCombinationLock::keyPressEvent(QKeyEvent* event)
{
    // Set the direction of typing (perspective of looking at 3D grids from the side)
    auto key = event->key();

    if(isNavigationKey(key))
    {
        switch (key)
        {
        case Qt::Key_PageDown:
            m_TypingDirection = DOWN;
            break;
        case Qt::Key_PageUp:
            m_TypingDirection = UP;
            break;
        case Qt::Key_Left:
            m_TypingDirection = ANTICLOCKWISE;
            break;
        case Qt::Key_Right:
            m_TypingDirection = CLOCKWISE;
            break;
        case Qt::Key_Plus:
            m_TypingDirection = DIAMETRIC;
            break;
        }
        selectNextGridShape();
    }

    GridScene3D::keyPressEvent(event);

    event->accept();
}

void GridSceneCombinationLock::keyReleaseEvent(QKeyEvent* event)
{
    GridScene3D::keyReleaseEvent(event);
}

bool GridSceneCombinationLock::isNavigationKey(int keyCode) const
{
    bool isNavigation = (keyCode == Qt::Key_PageDown ||
                         keyCode == Qt::Key_PageUp ||
                         keyCode == Qt::Key_Left ||
                         keyCode == Qt::Key_Right ||
                         keyCode == Qt::Key_Plus ||
                         keyCode == Qt::Key_Minus);

    return isNavigation;
}

bool GridSceneCombinationLock::selectNextGridShape()
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
    case DIAMETRIC:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::DIAMETRIC, current);
        break;
    case ANTICLOCKWISE:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::ANTICLOCKWISE, current);
        break;
    case CLOCKWISE:
        // Since (0,0) is at the upper left of a grid, pressing "towards" the front of the puzzle actually goes "down" the page
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::CLOCKWISE, current);
        break;
    case UP:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::UP, current);
        break;
    case DOWN:
        next = state->getNextCoordinateForDirection(Crossword::Formats::Direction::DOWN, current);
        break;
    }

    auto shape = getGridShapeForCoordinate(next);

    clearSelection();

    addCommand(new SelectGridItemCommand(shape));

    return true;
}

GridShape* GridSceneCombinationLock::getGridShapeForCoordinate(VectorMath::Vec3i coordinate)
{
    // TODO
    auto gridX = getCrosswordInterface()->getGridDimensions().x();
    auto gridY = getCrosswordInterface()->getGridDimensions().y();

    return getGridShapes().at(coordinate.x() + (coordinate.y() * gridX) + (coordinate.z() * gridX * gridY));
}

}
