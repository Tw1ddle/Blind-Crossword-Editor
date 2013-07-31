#ifndef CROSSWORDITEM_H
#define CROSSWORDITEM_H

#include <QString>
#include <QColor>

namespace Crossword
{

// Models a letter, string or symbol that belongs inside a crossword grid cell and grid item styling information
class CrosswordItem
{
public:
    CrosswordItem(const QString& text, const QColor& colour);

    const QString& getText() const;

private:
    QString m_Text;
    QColor m_Colour;
};

}

#endif // CROSSWORDITEM_H
