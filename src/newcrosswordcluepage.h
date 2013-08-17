#ifndef NEWCROSSWORDCLUEPAGE_H
#define NEWCROSSWORDCLUEPAGE_H

#include <QDialog>

namespace Ui
{
    class NewCrosswordCluePage;
}

namespace Editor
{

class NewCrosswordCluePage : public QDialog
{
    Q_OBJECT
public:
    explicit NewCrosswordCluePage(QWidget* parent = 0);
    ~NewCrosswordCluePage();

private:
    Ui::NewCrosswordCluePage* ui;
};

}

#endif // NEWCROSSWORDCLUEPAGE_H
