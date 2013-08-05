#ifndef GRIDSCENECOMBINATIONLOCK_H
#define GRIDSCENECOMBINATIONLOCK_H

#include "gridscene3d.h"

namespace Grid
{

class GridSceneCombinationLock : public Grid::GridScene3D
{
public:
    GridSceneCombinationLock(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);

private:
    virtual void addGrid();
};

}

#endif // GRIDSCENECOMBINATIONLOCK_H
