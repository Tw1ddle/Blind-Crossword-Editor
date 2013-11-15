#ifndef NEWCROSSWORDPAGE_H
#define NEWCROSSWORDPAGE_H

#include <QDialog>

#include "crosswordbase.h"

namespace Ui
{
    class NewCrosswordPage;
}

namespace Editor
{

class NewCrosswordPage : public QDialog
{
    Q_OBJECT
public:
    explicit NewCrosswordPage(QWidget* parent = 0);
    ~NewCrosswordPage();

    std::unique_ptr<Crossword::CrosswordState> getState();
    
private:
    Ui::NewCrosswordPage* ui;
    std::unique_ptr<Crossword::CrosswordState> m_NewCrossword;

private slots:
    // On crossword template selection
    void quickSelected();
    void rectangularSelected();
    void combinationLockSelected();
    void barredSelected();
};

}

#endif // NEWCROSSWORDPAGE_H
