#ifndef GRIDSCENERECTANGULARLAYERS_H
#define GRIDSCENERECTANGULARLAYERS_H

#include "gridscene3d.h"

namespace Grid
{

class GridSceneRectangularLayers : public Grid::GridScene3D
{
public:
    GridSceneRectangularLayers(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);
};

}

#endif // GRIDSCENERECTANGULARLAYERS_H
