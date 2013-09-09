#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include "gridshape.h"

namespace Grid
{

class GridSquare : public GridShape
{
public:
    GridSquare(Crossword::CrosswordItem& item, float width, float height);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);

private:
};

}

#endif // GRIDSQUARE_H
