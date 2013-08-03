#ifndef CONTRIBUTORSPAGE_H
#define CONTRIBUTORSPAGE_H

#include <QDialog>

namespace Ui {
class ContributorsPage;
}

namespace AppInfo
{

class ContributorsPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit ContributorsPage(QWidget *parent = 0);
    ~ContributorsPage();
    
private:
    Ui::ContributorsPage *ui;
};

}

#endif // CONTRIBUTORSPAGE_H
