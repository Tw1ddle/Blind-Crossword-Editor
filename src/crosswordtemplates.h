#ifndef CROSSWORDTEMPLATES_H
#define CROSSWORDTEMPLATES_H

#include "crosswordstate.h"

namespace Editor
{

namespace CrosswordTemplates
{

namespace Empty
{
    std::unique_ptr<Crossword::CrosswordState> make2DGrid(int x, int y);
    std::unique_ptr<Crossword::CrosswordState> make3DGrid(int x, int y, int z);
    std::unique_ptr<Crossword::CrosswordState> make3DCombinationLock(int radius, int segments, int depth);
}

}

}

#endif // CROSSWORDTEMPLATES_H
