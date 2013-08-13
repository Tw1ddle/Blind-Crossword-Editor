#include "plaintextsaver.h"

#include "utilities.h"

namespace Crossword
{

namespace Formats
{

PlainTextSaver::PlainTextSaver()
{
}

bool PlainTextSaver::save(const QString& filepath, const CrosswordState& state) const
{
    QFile file(filepath);

    QStringList lines;

    // Metadata
    auto& fileFormat = state.m_FileFormat;

    lines += fileFormat.m_Extension;
    lines += fileFormat.m_Version;

    auto& metadata = state.m_Metadata;

    lines += metadata.m_Title;
    lines += metadata.m_Authors;
    lines += metadata.m_Type;
    lines += metadata.m_Notes;

    // Don't need to print these out, really
    auto& dataSources = state.m_DataSources;
    Q_UNUSED(dataSources);

    // Clues
    auto& clues = state.m_ClueState.m_Clues;

    for(auto& clue : clues)
    {
        QString clueString;

        // TODO save all the clue details
        clueString.append(clue.getClue());
        clueString.append(clue.getNumber());
        clueString.append(clue.getSolution());
        clueString.append(clue.getDirection());

        auto& letterPositions = clue.getLetterPositions();
        for(auto& letterPosition : letterPositions)
        {
            Q_UNUSED(letterPosition);
            // TODO append letter position
        }
    }

    auto success = Utilities::writeFile(file, lines);

    return success;
}

}
}
