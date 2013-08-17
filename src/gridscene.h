#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>
#include <QDebug>

#include "internalinterfaces.h"

namespace Grid
{

// Base class for scenes that display the crossword grids
class GridScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GridScene(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState);
    virtual ~GridScene();

protected:
    InternalInterface::CrosswordStateToGridScene* getCrosswordState();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    InternalInterface::CrosswordStateToGridScene* m_CrosswordState;
};

}

#endif // GRIDSCENE_H
