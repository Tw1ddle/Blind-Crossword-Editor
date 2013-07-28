#ifndef XWCSAVER_H
#define XWCSAVER_H

#include "crosswordsaver.h"

namespace Crossword
{

namespace Formats
{

class XWCSaver : public CrosswordSaver
{
public:
    XWCSaver();

    virtual bool save(const QString& filepath, const CrosswordState& state) const override;
};

}

}

#endif // XWCSAVER_H
