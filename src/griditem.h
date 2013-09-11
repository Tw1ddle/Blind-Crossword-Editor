#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>
#include <QPen>

#include "vectormath.h"

namespace Grid
{

// Base class for items that appear in the scene - grid squares etc
class GridItem : public QGraphicsItem
{
public:
    explicit GridItem(QGraphicsItem* parent = 0);

    virtual QRectF boundingRect() const = 0;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) = 0;
    virtual void clear() = 0;

protected:
    QPen& getPen();

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value) override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

private:
    QPen m_Pen;
};

}

#endif // GRIDITEM_H
