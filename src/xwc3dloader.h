#ifndef XWC3DLOADER_H
#define XWC3DLOADER_H

#include "crosswordformat.h"
#include "crosswordloader.h"

namespace Crossword
{

namespace Formats
{

class XWC3DLoader : public CrosswordLoader
{
public:
    XWC3DLoader();

    virtual bool load(const QString& filepath, CrosswordState& puzzle) const override;
};

}
}

#endif // XWC3DLOADER_H
