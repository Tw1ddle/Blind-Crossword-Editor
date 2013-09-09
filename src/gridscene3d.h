#ifndef GRIDSCENE3D_H
#define GRIDSCENE3D_H

#include "gridscene.h"

namespace Grid
{

// Base class for 3D crossword puzzles
class GridScene3D : public Grid::GridScene
{
public:
    GridScene3D(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);

private:
    virtual bool advance() override;
};

}

#endif // GRIDSCENE3D_H
