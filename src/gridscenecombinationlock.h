#ifndef GRIDSCENECOMBINATIONLOCK_H
#define GRIDSCENECOMBINATIONLOCK_H

#include "gridscene3d.h"

namespace Grid
{

class GridSceneCombinationLock : public Grid::GridScene3D
{
public:
    GridSceneCombinationLock(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);

protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

private:
    virtual bool selectNextGridShape() override;
    virtual void addGrid();
    virtual bool isNavigationKey(int keyCode) const override;
    virtual GridShape* getGridShapeForCoordinate(VectorMath::Vec3i coordinate) override;

    enum UserTypingDirection
    {
        DIAMETRIC,
        CLOCKWISE,
        ANTICLOCKWISE,
        DOWN,
        UP
    };
    UserTypingDirection m_TypingDirection;
};

}

#endif // GRIDSCENECOMBINATIONLOCK_H
