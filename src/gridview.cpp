#include "gridview.h"

#include <QWheelEvent>

#include "gridscene.h"

using namespace Grid;

GridView::GridView(QWidget *parent) :
    QGraphicsView(parent)
{
    setScene(new GridScene(this));
}

void GridView::wheelEvent(QWheelEvent* event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    const double scaleFactor = 1.15;
    const double invScaleFactor = 1.0 / scaleFactor;

    if(event->delta() > 0)
    {
        scale(scaleFactor, scaleFactor);
    }
    else
    {
        scale(invScaleFactor, invScaleFactor);
    }
}
