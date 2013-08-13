#ifndef CROSSWORDSAVINGTEST_H
#define CROSSWORDSAVINGTEST_H

#include <QObject>
#include <QStringList>

#include "crosswordformatsupportlocator.h"

namespace Tests
{

class CrosswordSavingTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    // Loads and then saves known crossword states to and from the same formats
    // Compares the saved files to saves that are known to be correct
    void checkExpectedOutputs();

    // Saves a crossword state to all the supported save formats
    void saveToSupportedFormats();

    // Overrwrite an existing crossword file
    void overwriteFile();

    void cleanupTestCase();

    // Helper methods
    void loadFile(const QString& filepath);
    void saveFile(const QString& filepath);
};

}

#endif // CROSSWORDSAVINGTEST_H
