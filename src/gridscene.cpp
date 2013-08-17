#include "gridscene.h"

using namespace Grid;

#include <QString>
#include <QGraphicsTextItem>
#include <QTextStream>

#include <QGraphicsSceneMouseEvent>

#include "newcrosswordcluepage.h"

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

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* itemUnderMouse = itemAt(QPointF(event->scenePos().x(), event->scenePos().y()), QTransform());

    // Toggles whether the item is selected or not
    if(itemUnderMouse == nullptr)
    {
        return;
    }
    else if(itemUnderMouse->isEnabled() && (itemUnderMouse->flags() & QGraphicsItem::ItemIsSelectable))
    {
        itemUnderMouse->setSelected(true);
    }

    Editor::NewCrosswordCluePage newCluePage;

    newCluePage.exec();
}
