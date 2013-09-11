#include "gridscene3d.h"

namespace Grid
{

GridScene3D::GridScene3D(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) : GridScene(parent, crosswordState)
{
}

bool GridScene3D::advance()
{
    // TODO
    return false;
}

void GridScene3D::addGrid()
{
    // TODO
}

GridShape* GridScene3D::getGridShapeForCoordinate(VectorMath::Vec3i coordinate)
{
    // TODO
    Q_UNUSED(coordinate);

    return nullptr;
}

}
