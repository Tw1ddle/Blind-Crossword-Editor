#ifndef GRIDSHAPE_H
#define GRIDSHAPE_H

#include "griditem.h"

#include "crossworditem.h"

namespace Grid
{

class GridShape : public GridItem
{
public:
    GridShape(Crossword::CrosswordItem& item, float width, float height);

    virtual Crossword::CrosswordItem& getItem();

    virtual void clear() override;

protected:
    Crossword::CrosswordItem& m_Item;

    float m_Width;
    float m_Height;
};

}

#endif // GRIDSHAPE_H
