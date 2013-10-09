#include "gridclue.h"

#include <QPainter>
#include <QPen>

#include "appsettings.h"

namespace Grid
{

GridClue::GridClue(const Crossword::CrosswordClue& clue, float width, float height) : GridItem(), m_Clue(clue), m_Width(width), m_Height(height)
{
}

QRectF GridClue::boundingRect() const
{
    return QRectF(0, 0, m_Width, m_Height);
}

void GridClue::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(getPen());

    QString text = m_Clue.getNumber();

    // Empty cell
    if(!text.isNull())
    {
        // TODO fetch font from settings
        const Editor::Preferences::AppSettings settings;
        QString fontName = settings.getGridShapeFontName();

        int fontSize = settings.getGridShapeFontSize();

        Q_UNUSED(fontSize);

        QFont font;
        font.setFamily(fontName);
        font.setPixelSize(m_Width);

        painter->setFont(font);
        painter->drawText(boundingRect(), Qt::AlignCenter, text);
    }
}

void GridClue::clear()
{
    // TODO Note we don't clear the clue here (maybe do this later when it's all implemented properly)
}

void GridClue::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);
}

void GridClue::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
}

void GridClue::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    Q_UNUSED(event);
}

}
