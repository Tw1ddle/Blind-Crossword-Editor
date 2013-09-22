#ifndef XWC3DCOMMON_H
#define XWC3DCOMMON_H

#include <QMap>
#include <QChar>

namespace Crossword
{

namespace Formats
{

namespace XWC3D
{

enum class Modes
{
    WITHOUT_ANSWERS,
    WITH_ANSWERS,
    WITH_ANSWERS_UNSTARTED
};

class Common
{
public:
    static const QMap<QString, Modes> getModes(); // Map puzzle type/mode enum to identifier strings

    static const QChar whiteSquare; // White empty squares
    static const QChar blackSquare; // Black filled-in squares
    static const QChar clueAttributeSeparator; // The separator between elements of clues
    static const QChar highlightAttributeSeparator; // The separator between highlights of clues
    static const QChar subAttributeSeparator; // The separators between subattributes e.g. each coordinate of clues
};

}

}

}

#endif // XWC3DCOMMON_H
