#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QGraphicsView>

#include "internalinterfaces.h"

namespace Grid
{

class GridView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GridView(QWidget *parent = 0);

    void fitSceneInView();

protected:
    void wheelEvent(QWheelEvent* event);
    
signals:
    
public slots:

private:
    double m_CurrentZoom; // For keeping track of and limiting the zoom level of the view
    const double m_UpperZoomLimit;
    const double m_LowerZoomLimit;
};

}

#endif // GRIDVIEW_H
