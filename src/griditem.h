#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsItem>

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

private:

signals:
    
public slots:
    
};

}

#endif // GRIDITEM_H
