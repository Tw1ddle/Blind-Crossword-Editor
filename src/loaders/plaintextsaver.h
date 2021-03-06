#ifndef PLAINTEXTSAVER_H
#define PLAINTEXTSAVER_H

#include "crosswordsaver.h"

namespace Crossword
{

namespace Formats
{

class PlainTextSaver : public CrosswordSaver
{
public:
    PlainTextSaver();

    virtual QStringList save(const CrosswordState& state) const override;
};

}
}

#endif // PLAINTEXTSAVER_H
