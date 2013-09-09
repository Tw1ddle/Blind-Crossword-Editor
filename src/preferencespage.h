#ifndef PREFERENCESPAGE_H
#define PREFERENCESPAGE_H

#include <QDialog>

namespace Ui
{
    class PreferencesPage;
}

namespace Editor
{

namespace Preferences
{

class PreferencesPage : public QDialog
{
    Q_OBJECT
    
public:
    explicit PreferencesPage(QWidget *parent = 0);
    ~PreferencesPage();
    
private:
    void setupFolders();

    Ui::PreferencesPage *ui;
};

}

}

#endif // PREFERENCESPAGE_H
