#include "formatscommon.h"

namespace Crossword
{

namespace Formats
{

const QMap<QString, Directions> Common::getDirections()
{
    QMap<QString, Directions> map;
    map.insert("Across", Directions::ACROSS);
    map.insert("Backwards", Directions::BACKWARDS);
    map.insert("Away", Directions::AWAY);
    map.insert("Towards", Directions::TOWARDS);
    map.insert("Down", Directions::DOWN);
    map.insert("Up", Directions::UP);
    map.insert("Snaking", Directions::SNAKING);
    map.insert("Unknown", Directions::UNKNOWN);
    map.insert("None", Directions::NONE);

    return map;
}

}
}
