#include "xwcloader.h"

using namespace Crossword;

XWCLoader::XWCLoader() : CrosswordLoader()
{
}

bool XWCLoader::load(const QString& filepath, CrosswordState& state) const
{
    Q_UNUSED(filepath);
    Q_UNUSED(state);

    return false;
}
