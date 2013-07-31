#include "gridsquare.h"

#include <QPainter>
#include <QPen>

namespace Grid
{

GridSquare::GridSquare(const Crossword::CrosswordItem& item, float width, float height) : m_Item(item), m_Width(width), m_Height(height)
{
}

void GridSquare::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen;
    pen.setWidth(1);
    painter->setPen(pen);

    painter->drawRect(0, 0, m_Width, m_Height);

    auto text = m_Item.getText();

    // Empty cell
    if(!text.isNull())
    {
        // TODO fetch font from settings
        QFont font;
        font.setFamily("Georgia");
        font.setPixelSize(m_Width);

        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignCenter, text);
    }
}

QRectF GridSquare::boundingRect() const
{
    return QRectF(0, 0, m_Width, m_Height);
}

}
