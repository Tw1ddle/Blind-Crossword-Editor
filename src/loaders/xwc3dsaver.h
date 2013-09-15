#ifndef XWC3DSAVER_H
#define XWC3DSAVER_H

#include "crosswordformat.h"
#include "crosswordsaver.h"
#include "formatscommon.h"

namespace Crossword
{

namespace Formats
{

class XWC3DSaver : public CrosswordSaver
{
public:
    XWC3DSaver();

    virtual bool save(const QString& filepath, const CrosswordState& state) const override;

private:
    bool saveCluesForDirection(const CrosswordState& state, QStringList& lines, Crossword::Formats::Direction direction) const;
};

}
}

#endif // XWC3DSAVER_H
