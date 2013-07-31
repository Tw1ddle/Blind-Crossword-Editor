#include "crossworditem.h"

namespace Crossword
{

CrosswordItem::CrosswordItem(const QString& text, const QColor& colour) : m_Text(text), m_Colour(colour)
{
}

const QString& CrosswordItem::getText() const
{
    return m_Text;
}

}
