#ifndef CROSSWORDSAVINGTEST_H
#define CROSSWORDSAVINGTEST_H

#include <QObject>
#include <QStringList>

#include "crosswordloadsupportlocator.h"

namespace Tests
{

class CrosswordSavingTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    // Saves a crossword state to all the supported save formats
    void saveToSupportedFormats();

    // Checks that files resaved in the same format remain the same as the originals
    void checkEquivalence();

    void checkEquivalent(const QStringList& first, const QStringList& second);

    void cleanupTestCase();

private:
    // Helper methods
    bool loadFile(Crossword::CrosswordState& state, const QString& filepath);
    QStringList saveFile(const Crossword::CrosswordState& state, const QString& extension);

    void testSaveFile(const Crossword::CrosswordState& state, const QString& filename, const QString& extension);

    Crossword::Formats::CrosswordLoadSupportLocator m_FormatSupport;

    // The maximum number of differences to warn about before going to next file
    static const int m_MaxNumDifferences = 6;
};

}

#endif // CROSSWORDSAVINGTEST_H
