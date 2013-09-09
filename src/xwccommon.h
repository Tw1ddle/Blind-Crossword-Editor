#ifndef XWCCOMMON_H
#define XWCCOMMON_H

#include <QMap>
#include <QChar>

namespace Crossword
{

namespace Formats
{

namespace XWC
{

enum class Modes
{
    SKELETON,
    SOLUTION,
    CLUE,
    SOLVE
};

class Common
{
public:
    static const QMap<QString, Modes> getModes(); // Map puzzle type/mode enum to identifier strings

    static const QChar whiteSquare; // White empty squares
    static const QChar blackSquare; // Black filled-in squares
    static const QChar clueAttributeSeparator; // The separator between elements of clues

    static const QString TXWordGridVersionIdentifier; // A version identifier (TODO ask Ian if there are other versions)
    static const QString TXWordGrid3VersionIdentifier; // A version identifier (TODO ask Ian if there are other versions)

};

}

}

}

#endif // XWCCOMMON_H
