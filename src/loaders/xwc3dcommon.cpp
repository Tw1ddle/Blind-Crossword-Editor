#include "xwc3dcommon.h"

#include <QString>

namespace Crossword
{

namespace Formats
{

namespace XWC3D
{

const QMap<QString, Modes> Common::getModes()
{
    QMap<QString, Modes> map;
    map.insert("With Answers", Modes::WITH_ANSWERS);
    map.insert("Without Answers", Modes::WITHOUT_ANSWERS);
    map.insert("With Answers Unstarted", Modes::WITH_ANSWERS_UNSTARTED);

    return map;
}

const QChar Common::whiteSquare = '0'; // If all the words have not yet been entered, there will be a '0' (zero) for each empty white square.
const QChar Common::blackSquare = '1'; // Lower case letters are used for the solution words, with a '1' for each black square.
const QChar Common::clueAttributeSeparator = '|'; // The separator between elements of clues
const QChar Common::highlightAttributeSeparator = '|';
const QChar Common::subAttributeSeparator = ',';

}

}

}
