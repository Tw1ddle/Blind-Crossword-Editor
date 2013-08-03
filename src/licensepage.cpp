#include "licensepage.h"
#include "ui_licensepage.h"

#include "appinfo.h"

namespace AppInfo
{

LicensePage::LicensePage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LicensePage)
{
    ui->setupUi(this);

    ui->textBrowser->setText(AppInfo::getLicenseText());
}

LicensePage::~LicensePage()
{
    delete ui;
}

}
