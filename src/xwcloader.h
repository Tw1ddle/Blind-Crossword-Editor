#ifndef XWCLOADER_H
#define XWCLOADER_H

#include "crosswordloader.h"
#include "crosswordformat.h"

namespace Crossword
{

class XWCLoader : public CrosswordLoader
{
public:
    XWCLoader();

    virtual bool load(const QString& filepath, CrosswordState& state) const override;
};

}

#endif // XWCLOADER_H
