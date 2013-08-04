#ifndef CROSSWORDFORMAT_H
#define CROSSWORDFORMAT_H

#include <QString>
#include <QMap>

namespace Crossword
{

namespace Formats
{
// Format version constants
const QString VERSION_UNKNOWN = "UNKNOWN"; // The version identifier might not be recoverable
const QString VERSION_NONE = "NONE"; // The format might not even have a version field

// Describes a crossword puzzle format that the application supports
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

// A 2D puzzle grid format used in Blind Gamer's Crossword Puzzle by Spoonbill Games (v1.0.0)
const std::pair<QString, QString> XWC101 = std::make_pair("xwc", "1.0.0");

// 3D puzzle grid format used in Blind Crossword 3D for Blind Crosswords Limited (v1.0.0)
// Rectangular/square grids and combination lock grids
// Original format shared the same file extension but has a different format header
const std::pair<QString, QString> XWC3D100 = std::make_pair("xwc3d", "1.0.0");
const std::pair<QString, QString> XWC3DR100 = std::make_pair("xwc3dr", "1.0.0");

// 3D puzzle grid format used in Blind Crossword 3D for Blind Crosswords Limited (v1.0.1)
// Rectangular/square grids
const std::pair<QString, QString> XWC3D101 = std::make_pair("xwc3d", "1.0.1");

// 3D puzzle grid format used in Blind Crossword 3D for Blind Crosswords Limited (v1.0.1)
// Combination lock grids
const std::pair<QString, QString> XWC3DR101 = std::make_pair("xwc3dr", "1.0.1");

// Across Lite's .PUZ format, see: https://code.google.com/p/puz/wiki/FileFormat
const std::pair<QString, QString> ACROSS_LITE_PUZ = std::make_pair("puz", Formats::VERSION_UNKNOWN);

// Crossword Compiler legacy formats
const std::pair<QString, QString> CROSSWORD_COMPILER_LEGACY = std::make_pair("ccw", Formats::VERSION_UNKNOWN);

// Crossword Compiler version 4.0-5.1
const std::pair<QString, QString> CROSSWORD_COMPILER_40_51 = std::make_pair("CC4", "4-5.1");

// More supported formats go here...

// Known crossword formats
// The code below is for deciding which type of grid scene to load
enum class FormatEnum
{
    XWC,
    XWC3D,
    XWC3DR,
    PUZ,
    CCW,
    CC4
};

// 2D format file extensions
const QMap<QString, FormatEnum> get2DFormats();

// 3D format file extensions
const QMap<QString, FormatEnum> get3DFormats();

// All puzzle file extensions
// Update this method if new format types are added in addition to 2D and 3D
const QMap<QString, FormatEnum> getAllFormats();

}

}

#endif // CROSSWORDFORMAT_H
