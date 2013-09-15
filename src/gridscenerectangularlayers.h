#ifndef GRIDSCENERECTANGULARLAYERS_H
#define GRIDSCENERECTANGULARLAYERS_H

#include "gridscene3d.h"

namespace Grid
{

class GridSceneRectangularLayers : public Grid::GridScene3D
{
public:
    GridSceneRectangularLayers(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);

protected:
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

private:
    virtual void addGrid(int gridNumber);

    virtual bool isNavigationKey(int keyCode) const override;
    virtual bool selectNextGridShape() override;

    virtual GridShape* getGridShapeForCoordinate(VectorMath::Vec3i coordinate) override;

    enum UserTypingDirection
    {
        RIGHT,
        LEFT,
        AWAY,
        TOWARDS,
        UP,
        DOWN
    };
    UserTypingDirection m_TypingDirection;
};

}

#endif // GRIDSCENERECTANGULARLAYERS_H
