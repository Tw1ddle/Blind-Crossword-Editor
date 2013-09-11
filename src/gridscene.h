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
    InternalInterface::CrosswordStateToGridScene* getCrosswordState();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void keyReleaseEvent(QKeyEvent* event) override;

    QList<Grid::GridShape*> getSelectedGridShapes();

    std::vector<GridShape*>& getGridShapes();

    virtual void typeInItems(const QString& text, QList<GridShape*>& items);
    virtual void onSelectionChanged();

    // Actions the user is performing on the grid
    enum UserState
    {
        FILLING_GRID,
        SELECTING_CLUE
    };
    UserState m_State;

    virtual GridShape* getGridShapeForCoordinate(VectorMath::Vec3i coordinate) = 0;

private:
    InternalInterface::CrosswordStateToGridScene* m_CrosswordState;

    void addClue();
    void createClueFromSelection();


    virtual bool advance() = 0; // Get the next item in the grid. Assumes puzzles have some concept of order or direction.
    virtual void addGrid() = 0; // Grid items (views) must be in the same order as the crossword grid item vector (models), so that coordinates are the same (to enable lookup rather than having pointers)

    bool m_LeftMouseDown;

    std::vector<GridShape*> m_GridShapes;
};

}

#endif // GRIDSCENE_H
