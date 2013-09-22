#ifndef ACROSSLITETEXTSAVER_H
#define ACROSSLITETEXTSAVER_H

#include "crosswordsaver.h"
#include "formatscommon.h"

namespace Crossword
{

namespace Formats
{

// TODO implement me
class AcrossLiteTextSaver : public CrosswordSaver
{
public:
    AcrossLiteTextSaver();

    virtual QStringList save(const CrosswordState& state) const override;

private:
};

}
}

#endif // ACROSSLITETEXTSAVER_H
