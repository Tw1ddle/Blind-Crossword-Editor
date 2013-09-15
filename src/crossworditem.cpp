#include "crossworditem.h"

namespace Crossword
{

CrosswordItem::CrosswordItem(const QString& text, const VectorMath::Vec3i& coordinate, const QColor& colour) : m_Text(text), m_Coordinate(coordinate), m_Colour(colour)
{
}

const QString& CrosswordItem::getText() const
{
    return m_Text;
}

void CrosswordItem::setText(const QString& text)
{
    m_Text = text;
}

void CrosswordItem::clear()
{
    // TODO do any languages use a glyph for the empty string?
    m_Text = "";
    m_Colour = Qt::white;
}

const VectorMath::Vec3i& CrosswordItem::getCoordinate() const
{
    return m_Coordinate;
}

const QColor& CrosswordItem::getColour() const
{
    return m_Colour;
}

}
