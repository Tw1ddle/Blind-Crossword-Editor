#include "gridscene.h"

using namespace Grid;

#include <QString>
#include <QGraphicsTextItem>
#include <QTextStream>

GridScene::GridScene(QObject* parent, InternalInterface::CrosswordStateToGridScene* const crosswordState) :
    QGraphicsScene(parent), m_CrosswordState(crosswordState)
{    
    // TODO draw a grid using pixmaps and LOD
    // Add a setting to show grid or not
}

GridScene::~GridScene()
{
}

InternalInterface::CrosswordStateToGridScene* GridScene::getCrosswordState()
{
    return m_CrosswordState;
}
