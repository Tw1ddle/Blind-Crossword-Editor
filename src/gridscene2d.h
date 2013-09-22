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

protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

private:
    virtual void addGrid(int gridNumber = 0);
    virtual bool selectNextGridShape() override;
    virtual GridShape* getGridShapeForCoordinate(VectorMath::Vec3i coordinate) override;

    enum UserTypingDirection
    {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };
    UserTypingDirection m_TypingDirection;

    virtual bool isNavigationKey(int keyCode) const override;
};

}

#endif // GRIDSCENE2D_H
