#include "gridview.h"

#include <QWheelEvent>

using namespace Grid;

GridView::GridView(QWidget* parent) :
    QGraphicsView(parent), m_CurrentZoom(1.0), m_UpperZoomLimit(20.0), m_LowerZoomLimit(0.5)
{
    setScene(new QGraphicsScene()); // Start with an empty scene
}

void GridView::fitSceneInView()
{
    fitInView(scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
    m_CurrentZoom = 1.0;
}

void GridView::wheelEvent(QWheelEvent* event)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    const double scaleFactor = 1.15;
    const double invScaleFactor = 1.0 / scaleFactor;

    if(event->delta() > 0)
    {
        if(m_CurrentZoom <= m_UpperZoomLimit)
        {
            m_CurrentZoom *= scaleFactor;
            scale(scaleFactor, scaleFactor);
        }
    }
    else
    {
        if(m_CurrentZoom >= m_LowerZoomLimit)
        {
            m_CurrentZoom *= invScaleFactor;
            scale(invScaleFactor, invScaleFactor);
        }
    }
}
