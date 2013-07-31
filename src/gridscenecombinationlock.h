#ifndef GRIDSCENECOMBINATIONLOCK_H
#define GRIDSCENECOMBINATIONLOCK_H

#include "gridscene3d.h"

namespace Grid
{

class GridSceneCombinationLock : public Grid::GridScene3D
{
public:
    GridSceneCombinationLock(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);
};

}

#endif // GRIDSCENECOMBINATIONLOCK_H
