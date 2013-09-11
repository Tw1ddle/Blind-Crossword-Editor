#ifndef WORDLIST_H
#define WORDLIST_H

#include <vector>
#include <tuple>
#include <QString>

namespace Editor
{

// A set of crossword clue solution words and cue data. Used for auto-filling the grid and/or providing suggestions
class WordList
{
public:
    WordList();

private:
    std::vector<std::tuple<QString>> m_Words;
};

}

#endif // WORDLIST_H
