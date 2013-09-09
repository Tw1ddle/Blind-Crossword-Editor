#include "gridsquare.h"

#include <QPainter>
#include <QPen>
#include <QList>

namespace Grid
{

GridSquare::GridSquare(Crossword::CrosswordItem& item, float width, float height) : GridShape(item, width, height)
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

void GridSquare::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    GridItem::mouseReleaseEvent(event);
}

void GridSquare::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    GridItem::hoverEnterEvent(event);
}

void GridSquare::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    GridItem::hoverLeaveEvent(event);
}

QVariant GridSquare::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    if(change == QGraphicsItem::ItemSelectedChange)
    {
        if(value == true)
        {
            // TODO change colour to setting
            getPen().setColor(QColor(Qt::green));
        }
        else if(value == false)
        {
            // TODO change colour to setting
            getPen().setColor(QColor(Qt::black));
        }
    }

    return GridItem::itemChange(change, value);
}

QRectF GridSquare::boundingRect() const
{
    return QRectF(0, 0, m_Width, m_Height);
}

}
