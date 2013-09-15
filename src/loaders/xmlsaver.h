#ifndef XMLSAVER_H
#define XMLSAVER_H

#include "crosswordsaver.h"

namespace Crossword
{

namespace Formats
{

class XMLSaver : public CrosswordSaver
{
public:
    XMLSaver();

    virtual bool save(const QString& filepath, const CrosswordState& state) const override;
};

}
}

#endif // XMLSAVER_H
