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

}
