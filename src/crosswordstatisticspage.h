#ifndef CROSSWORDSTATISTICSPAGE_H
#define CROSSWORDSTATISTICSPAGE_H

#include <QDialog>

namespace Crossword
{
    class CrosswordState;
}

namespace Ui
{
class CrosswordStatisticsPage;
}

namespace Editor
{

class CrosswordStatisticsPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit CrosswordStatisticsPage(QWidget *parent, const Crossword::CrosswordState& state);
    ~CrosswordStatisticsPage();
    
private:
    Ui::CrosswordStatisticsPage *ui;

    void setupContent(const Crossword::CrosswordState& state);
};

}

#endif // CROSSWORDSTATISTICSPAGE_H
