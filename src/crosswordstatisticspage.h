#ifndef CROSSWORDSTATISTICSPAGE_H
#define CROSSWORDSTATISTICSPAGE_H

#include <QDialog>

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
    explicit CrosswordStatisticsPage(QWidget *parent = 0);
    ~CrosswordStatisticsPage();
    
private:
    Ui::CrosswordStatisticsPage *ui;
};

}

#endif // CROSSWORDSTATISTICSPAGE_H
