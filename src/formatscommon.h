#ifndef FORMATSCOMMON_H
#define FORMATSCOMMON_H

#include <QMap>
#include <QString>

namespace Crossword
{

namespace Formats
{

enum class Directions
{
    // 2D puzzles
    ACROSS, // Left to right
    BACKWARDS, // Right to left
    AWAY, // Up the grid
    TOWARDS, // Down the grid

    // 3D puzzles
    DOWN, // Down through grids
    UP, // Up through grids

    // 3D combination lock-style puzzles
    DIAMETRIC, // Through the disc
    CIRCULAR, // Around a disc

    // All of the above
    SNAKING, // Each letter could be anywhere, turn corners etc
    UNKNOWN, // If the puzzle does not define a direction or it is something different
    NONE // If the clues in this type of puzzle really don't have any direction
};

class Common
{
public:
    static const QMap<QString, Directions> getDirections();
};

}
}

#endif // FORMATSCOMMON_H
