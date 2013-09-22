#ifndef XWCSAVER_H
#define XWCSAVER_H

#include "crosswordsaver.h"
#include "formatscommon.h"

namespace Crossword
{

namespace Formats
{

class XWCSaver : public CrosswordSaver
{
public:
    XWCSaver();

    virtual QStringList save(const CrosswordState& state) const override;

private:
    bool saveMetadata(const CrosswordState& state, QStringList& lines) const;
    bool saveGrid(const CrosswordState& state, QStringList& lines) const;
    bool saveClues(const CrosswordState& state, QStringList& lines) const;
    bool saveSolveGrid(const CrosswordState& state, QStringList& lines) const;

    bool saveCluesForDirection(const CrosswordState& state, QStringList& lines, Crossword::Formats::Direction direction) const;
};

}

}

#endif // XWCSAVER_H
