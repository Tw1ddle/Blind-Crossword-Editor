#include "gridscenecombinationlock.h"

namespace Grid
{

GridSceneCombinationLock::GridSceneCombinationLock(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) : GridScene3D(parent, crosswordState)
{
    m_TypingDirection = CLOCKWISE;
}

bool GridSceneCombinationLock::selectNextGridShape()
{
    // TODO
    return false;
}

void GridSceneCombinationLock::addGrid()
{
    // TODO
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

GridShape* GridSceneCombinationLock::getGridShapeForCoordinate(VectorMath::Vec3i coordinate)
{
    Q_UNUSED(coordinate);

    // TODO
    auto gridX = getCrosswordInterface()->getGridDimensions().x();
    auto gridY = getCrosswordInterface()->getGridDimensions().y();

    return getGridShapes().at(coordinate.x() + (coordinate.y() * gridX) + (coordinate.z() * gridX * gridY));
}

void GridSceneCombinationLock::keyPressEvent(QKeyEvent* event)
{
    Q_UNUSED(event);
}

void GridSceneCombinationLock::keyReleaseEvent(QKeyEvent* event)
{
    Q_UNUSED(event);
}

}
