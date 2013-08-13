#include "xwcsaver.h"

using namespace Crossword;
using namespace Crossword::Formats;

XWCSaver::XWCSaver() : CrosswordSaver()
{
}

bool XWCSaver::save(const QString& filepath, const CrosswordState& state) const
{
    // TODO note that locations of individual characters matter for this format e.g. "_9" "10" form.
    // See Ian's spec

    Q_UNUSED(filepath);
    Q_UNUSED(state);

    return false;
}
