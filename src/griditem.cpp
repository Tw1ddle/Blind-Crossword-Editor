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

QVariant GridItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    return QGraphicsItem::itemChange(change, value);
}

void GridItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mousePressEvent(event);
}

void GridItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem::mouseReleaseEvent(event);
}

void GridItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsItem::hoverEnterEvent(event);
}

void GridItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    QGraphicsItem::hoverLeaveEvent(event);
}
