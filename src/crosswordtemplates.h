#ifndef CROSSWORDTEMPLATES_H
#define CROSSWORDTEMPLATES_H

#include "crosswordstate.h"

namespace Editor
{

namespace CrosswordTemplates
{

namespace Empty
{
    Crossword::CrosswordState make2DGrid(int x, int y);
    Crossword::CrosswordState make3DGrid(int x, int y, int z);
    Crossword::CrosswordState make3DCombinationLock(int radius, int segments, int depth);
}

}

}

#endif // CROSSWORDTEMPLATES_H
