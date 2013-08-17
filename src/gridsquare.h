#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include "griditem.h"

#include "crossworditem.h"

namespace Grid
{

class GridSquare : public GridItem
{
public:
    GridSquare(Crossword::CrosswordItem& item, float width, float height);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    Crossword::CrosswordItem& m_Item;

    float m_Width;
    float m_Height;
};

}

#endif // GRIDSQUARE_H
