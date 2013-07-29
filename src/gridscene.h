#ifndef GRIDSCENE_H
#define GRIDSCENE_H

#include <QGraphicsScene>

namespace Grid
{

// Base class for scenes that display the crossword grids
class GridScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GridScene(QObject *parent = 0);
    
signals:
    
public slots:
    
};

}

#endif // GRIDSCENE_H
