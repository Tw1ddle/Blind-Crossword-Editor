#include "gridshape.h"

namespace Grid
{

GridShape::GridShape(Crossword::CrosswordItem& item, float width, float height) : m_Item(item), m_Width(width), m_Height(height)
{
}

Crossword::CrosswordItem& GridShape::getItem()
{
    return m_Item;
}

void GridShape::setItem(const Crossword::CrosswordItem& item)
{
    m_Item = item;
}

void GridShape::clear()
{
    m_Item.clear();
}

}
