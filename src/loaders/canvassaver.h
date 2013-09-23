#ifndef CANVASSAVER_H
#define CANVASSAVER_H

#include "crosswordformat.h"
#include "crosswordsaver.h"

namespace Crossword
{

namespace Formats
{

class CanvasSaver : public CrosswordSaver
{
public:
    CanvasSaver();

    // Saves an XML file which is bundled with the Canvas code
    virtual QStringList save(const CrosswordState& state) const;
};

}
}


#endif // CANVASSAVER_H
