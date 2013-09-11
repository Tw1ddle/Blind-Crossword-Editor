#ifndef FORMATSCOMMON_H
#define FORMATSCOMMON_H

#include <QMap>
#include <QString>

#include "crosswordclue.h"

namespace Crossword
{

namespace Formats
{

enum class Direction
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
    CLOCKWISE, // Around a disc
    ANTICLOCKWISE, // The other way

    // All of the above
    SNAKING, // Each letter could be anywhere, turn corners etc
    UNKNOWN // If the puzzle does not define a direction or it is something different
};

class Common
{
public:
    static const QMap<QString, Direction> getDirections();
};

Direction getDirection(std::vector<VectorMath::Vec3i> letterPositions);
Direction getDirection(const QString& direction);

}
}

#endif // FORMATSCOMMON_H
