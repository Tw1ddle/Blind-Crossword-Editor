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

    virtual bool save(const QString& filepath, const CrosswordState& state) const override;

private:
    bool saveCluesForDirection(const CrosswordState& state, QStringList& lines, Crossword::Formats::Direction direction) const;
};

}

}

#endif // XWCSAVER_H
