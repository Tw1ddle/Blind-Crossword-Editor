#ifndef GRIDSQUARE_H
#define GRIDSQUARE_H

#include "griditem.h"

#include "crossworditem.h"

namespace Grid
{

class GridSquare : public GridItem
{
public:
    GridSquare(const Crossword::CrosswordItem& item, float width, float height);

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

private:
    const Crossword::CrosswordItem& m_Item;

    float m_Width;
    float m_Height;
};

}

#endif // GRIDSQUARE_H
