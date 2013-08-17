#ifndef CROSSWORDSTATISTICS_H
#define CROSSWORDSTATISTICS_H

#include <QString>

#include "crosswordstate.h"

namespace Editor
{

// Get stats about a crossword
QString numLettersInGrid(const Crossword::CrosswordState& state);
QString numItemsInGrid(const Crossword::CrosswordState& state);
QString numEmptiesInGrid(const Crossword::CrosswordState& state);

}

#endif // CROSSWORDSTATISTICS_H
