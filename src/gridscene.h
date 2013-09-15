#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QDebug>

#include "internalinterfaces.h"

namespace Grid
{

class GridShape;

// Base class for scenes that display the crossword grids
class GridScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GridScene(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);
    virtual ~GridScene();

protected:
    InternalInterface::CrosswordStateToGridScene* getCrosswordInterface();

    // Input handling
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

    // Grid getters
    QList<Grid::GridShape*> getSelectedGridShapes();
    std::vector<GridShape*>& getGridShapes();
    virtual GridShape* getGridShapeForCoordinate(VectorMath::Vec3i coordinate) = 0;

    // Grid editing
    virtual void typeInItems(const QString& text, QList<GridShape*>& items);
    virtual void onSelectionChanged();

    // Actions the user performs
    enum UserState
    {
        FILLING_GRID,
        SELECTING_CLUE
    };
    UserState m_State;

private:
    void addClue();
    void createClueFromSelection();
    virtual bool selectNextGridShape() = 0; // Get the next item in the grid. Assumes puzzles have some concept of order or direction.
    virtual bool isNavigationKey(int keyCode) const = 0; // Controls allow user to most around the grid using certain keys

    std::vector<GridShape*> m_GridShapes;
    InternalInterface::CrosswordStateToGridScene* m_CrosswordState;
    bool m_LeftMouseDown;
};

}

#endif // GRIDSCENE_H
