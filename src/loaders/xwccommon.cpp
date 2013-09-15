#include "xwccommon.h"

#include <QString>

namespace Crossword
{

namespace Formats
{

namespace XWC
{

const QMap<QString, Modes> Common::getModes()
{
    QMap<QString, Modes> map;
    map.insert("Skeleton", Modes::SKELETON);
    map.insert("Solution", Modes::SOLUTION);
    map.insert("Clue", Modes::CLUE);
    map.insert("Solve", Modes::SOLVE);

    return map;
}

const QChar Common::whiteSquare = '0'; // If all the words have not yet been entered, there will be a '0' (zero) for each empty white square.
const QChar Common::blackSquare = '1'; // Lower case letters are used for the solution words, with a '1' for each black square.
const QChar Common::clueAttributeSeparator = '|'; // The separator between elements of clues

const QString Common::TXWordGridVersionIdentifier = "TXWordGrid"; // A version identifier
const QString Common::TXWordGrid3VersionIdentifier = "TXWordGrid3"; // A version identifier

}

}

}
