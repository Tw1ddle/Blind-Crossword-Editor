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

    auto& metadata = state.m_Metadata;

    lines += metadata.m_Title;
    lines += metadata.m_Authors;
    lines += metadata.m_Type;
    lines += metadata.m_Notes;

    // Clues
    auto& clues = state.m_ClueState.m_Clues;

    for(auto& clue : clues)
    {
        QString clueString;

        clueString += clue.getNumber() + " ";
        clueString += clue.getDirection() + " ";
        clueString += clue.getClue() + " ";
        clueString += clue.getSolution() + " ";


        auto& letterPositions = clue.getLetterPositions();
        for(auto& letterPosition : letterPositions)
        {
            clueString += QString::number(letterPosition.x()) + ",";
            clueString += QString::number(letterPosition.y()) + ",";
            clueString += QString::number(letterPosition.z());
            clueString += "|";
        }

        lines += clueString;
    }

    auto success = Utilities::writeFile(file, lines);

    return success;
}

}
}
