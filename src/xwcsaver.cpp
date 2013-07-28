#include "xwcsaver.h"

using namespace Crossword;
using namespace Crossword::Formats;

XWCSaver::XWCSaver() : CrosswordSaver()
{
}

bool XWCSaver::save(const QString& filepath, const CrosswordState& state) const
{
    Q_UNUSED(filepath);
    Q_UNUSED(state);

    return false;
}
