#ifndef LICENSEPAGE_H
#define LICENSEPAGE_H

#include <QDialog>

namespace Ui
{
    class LicensePage;
}

namespace AppInfo
{

class LicensePage : public QDialog
{
    Q_OBJECT
    
public:
    explicit LicensePage(QWidget *parent = 0);
    ~LicensePage();
    
private:
    Ui::LicensePage *ui;
};

}

#endif // LICENSEPAGE_H
