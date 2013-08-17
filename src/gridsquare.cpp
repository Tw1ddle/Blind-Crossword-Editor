#include "gridsquare.h"

#include <QPainter>
#include <QPen>

namespace Grid
{

GridSquare::GridSquare(Crossword::CrosswordItem& item, float width, float height) : m_Item(item), m_Width(width), m_Height(height)
{
}

void GridSquare::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(getPen());

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

void GridSquare::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    GridItem::mousePressEvent(event);
}

void GridSquare::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    getPen().setColor(QColor(Qt::red));

    GridItem::hoverEnterEvent(event);
}

void GridSquare::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    getPen().setColor(QColor(Qt::blue));

    GridItem::hoverLeaveEvent(event);
}

QRectF GridSquare::boundingRect() const
{
    return QRectF(0, 0, m_Width, m_Height);
}

}
