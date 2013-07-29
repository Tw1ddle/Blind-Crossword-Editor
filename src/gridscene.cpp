#include "gridscene.h"

using namespace Grid;

#include <QString>
#include <QGraphicsTextItem>
#include <QTextStream>

GridScene::GridScene(QObject *parent) :
    QGraphicsScene(parent)
{
    // Draw a grid with coordinates
    for(int x = 0; x < 1000; x = x + 25)
    {
        for(int y = 0; y < 1000; y = y + 25)
        {

            if(x % 100 == 0 && y % 100 == 0)
            {
                addRect(x, y, 2, 2);

                QString pointString;
                QTextStream stream(&pointString);
                stream << "(" << x << "," << y << ")";
                QGraphicsTextItem* item = addText(pointString);
                item->setPos(x, y);
            }
            else
            {
                addRect(x, y, 1, 1);
            }
        }
    }
}
