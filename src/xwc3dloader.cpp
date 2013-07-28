#include "xwc3dloader.h"

using namespace Crossword;
using namespace Crossword::Formats;

XWC3DLoader::XWC3DLoader()
{
}

bool Crossword::Formats::XWC3DLoader::load(const QString& filepath, Crossword::CrosswordState& puzzle) const
{
    Q_UNUSED(filepath);
    Q_UNUSED(puzzle);

    return false;
}
