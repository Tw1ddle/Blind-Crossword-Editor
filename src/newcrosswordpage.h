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
};

}

#endif // NEWCROSSWORDPAGE_H
