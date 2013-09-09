#ifndef GRIDFILLALGORITHM_H
#define GRIDFILLALGORITHM_H

#include "crosswordclue.h"

// TODO A grid filling algorithm takes a word list and a set of clue coordinates
// Information inferred from this by the algorithm lets it fill the grid

namespace Editor
{

class GridFillAlgorithm
{
public:
    GridFillAlgorithm(std::vector<Crossword::CrosswordClue>& clues);

    virtual void fill() = 0;

private:
};

}

#endif // GRIDFILLALGORITHM_H
