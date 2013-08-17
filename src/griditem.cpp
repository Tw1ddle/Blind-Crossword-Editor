#include "griditem.h"

using namespace Grid;

GridItem::GridItem(QGraphicsItem* parent) :
    QGraphicsItem(parent)
{
    setFlags(QGraphicsItem::ItemIsSelectable);

    setAcceptHoverEvents(true);
}

QPen& GridItem::getPen()
{
    return m_Pen;
}

void GridItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
}

void GridItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsItem::hoverEnterEvent(event);
}

void GridItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}
