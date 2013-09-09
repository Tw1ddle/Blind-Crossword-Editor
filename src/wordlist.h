#ifndef WORDLIST_H
#define WORDLIST_H

#include <vector>
#include <tuple>
#include <QString>

// A set of crossword clue solution words. Used for auto-filling the grid and providing suggestions
class WordList
{
public:
    WordList();

private:
    std::vector<std::tuple<QString>> m_Words;
};

#endif // WORDLIST_H
