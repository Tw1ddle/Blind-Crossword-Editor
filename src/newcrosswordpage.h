#ifndef NEWCROSSWORDPAGE_H
#define NEWCROSSWORDPAGE_H

#include <QDialog>

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
    
private:
    Ui::NewCrosswordPage* ui;

    void setupContent();

private slots:
    // On crossword template selection
    void quickSelected();
    void rectangularSelected();
    void combinationLockSelected();
    void barredSelected();
};

}

#endif // NEWCROSSWORDPAGE_H
