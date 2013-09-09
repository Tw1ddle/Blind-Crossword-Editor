#ifndef GRIDCLUE_H
#define GRIDCLUE_H

#include "griditem.h"
#include "crosswordclue.h"

namespace Grid
{

class GridClue : public GridItem
{
public:
    GridClue(const Crossword::CrosswordClue& item, float width, float height);

    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0) override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

private:
    const Crossword::CrosswordClue& m_Clue;

    float m_Width;
    float m_Height;
};

}

#endif // GRIDCLUE_H
