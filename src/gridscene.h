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

    virtual void typeInItems(const QString& text, QList<GridShape*>& items);

    // Actions the user is performing on the grid
    enum UserState
    {
        FILLING_GRID,
        SELECTING_CLUE
    };

private:
    InternalInterface::CrosswordStateToGridScene* m_CrosswordState;

    void addClue();
    void createClueFromSelection();
    virtual bool advance() = 0; // Get the next item in the grid. Assumes puzzles have some concept of order or direction.

    bool m_LeftMouseDown;

    UserState m_State;
};

}

#endif // GRIDSCENE_H
