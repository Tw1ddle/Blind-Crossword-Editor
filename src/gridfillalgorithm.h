#ifndef GRIDFILLALGORITHM_H
#define GRIDFILLALGORITHM_H

#include "crosswordclue.h"

// Takes a word list and a set of clues (that contain grid coordinates)
// Information inferred from this data lets the algorithm fill the grid

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
