#ifndef CROSSWORDITEM_H
#define CROSSWORDITEM_H

#include <QString>
#include <QColor>

#include "vectormath.h"

namespace Crossword
{

// Models a letter, string or symbol that belongs inside a crossword grid cell and grid item styling information
class CrosswordItem
{
public:
    CrosswordItem(const QString& text, const VectorMath::Vec3i& coordinate, const QColor& colour);

    const QString& getText() const;
    const VectorMath::Vec3i& getCoordinate() const;
    void setText(const QString& text);

    virtual void clear();

private:
    QString m_Text;
    QColor m_Colour;
    VectorMath::Vec3i m_Coordinate;
};

}

#endif // CROSSWORDITEM_H
