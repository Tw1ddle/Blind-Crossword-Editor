#include "testrunner.h"

#include <QTest>
#include <QDir>
#include <QStringList>

#include "crosswordloadingtest.h"
#include "crosswordsavingtest.h"

namespace Tests
{

TestRunner::TestRunner()
{
    // Output options
    QStringList testCommand;
    QDir testLogDirectory;

    testLogDirectory.mkdir("UnitTest_Results");
    testCommand << "-xml" << "-o" << "UnitTest_Results/test_log.xml";

    // Run some tests
    CrosswordLoadingTest crosswordLoadingTest;

    QTest::qExec(&crosswordLoadingTest, testCommand);

    CrosswordSavingTest crosswordSavingTest;

    QTest::qExec(&crosswordSavingTest, testCommand);
}

}
