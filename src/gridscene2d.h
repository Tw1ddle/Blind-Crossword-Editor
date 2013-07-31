#ifndef GRIDSCENE2D_H
#define GRIDSCENE2D_H

#include "gridscene.h"
#include "gridsquare.h"

namespace Grid
{

// Scene for ordinary 2D crossword grids
class GridScene2D : public Grid::GridScene
{
public:
    GridScene2D(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);

private:
    virtual void addGrid();
};

}

#endif // GRIDSCENE2D_H
