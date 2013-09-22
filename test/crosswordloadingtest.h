#ifndef CROSSWORDLOADINGTEST_H
#define CROSSWORDLOADINGTEST_H

#include <QObject>
#include <QStringList>

#include "crosswordloadsupportlocator.h"

namespace Tests
{

// Tests the ability of the program to load different types of crosswords
class CrosswordLoadingTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    // Tests that the loaders actually work by applying test files to them.
    // Load up a series of working puzzles
    void loadValidCrosswords();
    // Load up valid files with foreign names, non-Roman characters etc
    void loadUnusualCrosswords();
    // Broken puzzles and invalid files
    void loadBrokenCrosswords();

    // Tests whether the program correctly rejects non-crossword files
    // Non-crossword files
    void loadInvalidFiles();

    void cleanupTestCase();

private:
    bool loadCrosswords(QString testPath);

    Crossword::CrosswordState m_State;
    Crossword::Formats::CrosswordLoadSupportLocator m_FormatSupport;
};

}

#endif // CROSSWORDLOADINGTEST_H
