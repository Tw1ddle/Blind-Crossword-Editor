#ifndef CROSSWORDFORMAT_H
#define CROSSWORDFORMAT_H

#include <QString>

namespace Crossword
{

namespace Formats
{

// Format version constants
const QString VERSION_UNKNOWN = "UNKNOWN"; // The version identifier might not be recoverable
const QString VERSION_NONE = "NONE"; // The format might not even have a version field

// Describes a crossword puzzle format that the application (might) support
class CrosswordFormat
{
public:
    CrosswordFormat(const QString& fileExtension, const QString& version = VERSION_UNKNOWN);
    CrosswordFormat(const std::pair<QString, QString>& pair);

    virtual const QString& getExtension() const;
    virtual const QString& getVersion() const;

private:
    const QString m_Extension;
    const QString m_Version;
};

// A 2D puzzle grid format used in Blind Gamer's Crossword Puzzle by Spoonbill Games (v1.0.1)
const std::pair<QString, QString> XWC101 = std::make_pair("xwc", "1.0.1");

// 3D puzzle grid format used in Blind Crossword 3D for Blind Crosswords Limited (v1.0.1)
const std::pair<QString, QString> XWC3D101 = std::make_pair("xwc3d", "1.0.1");

// More formats go here...

}

}

#endif // CROSSWORDFORMAT_H
