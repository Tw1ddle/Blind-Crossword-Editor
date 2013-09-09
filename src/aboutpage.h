#ifndef ABOUTPAGE_H
#define ABOUTPAGE_H

#include <QDialog>

namespace Ui
{
    class AboutPage;
}

namespace AppInfo
{

class AboutPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutPage(QWidget *parent = 0);
    ~AboutPage();

public slots:
    void showLicensePage();
    void showContributorsPage();
    void showAboutQt();
    
private:
    Ui::AboutPage *ui;

private slots:
};

}

#endif // ABOUTPAGE_H
