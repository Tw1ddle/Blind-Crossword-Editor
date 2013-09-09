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
QString numClues(const Crossword::CrosswordState& state);

QString numCluesForDirection(const Crossword::CrosswordState& state, const QString& direction);

}

#endif // CROSSWORDSTATISTICS_H
