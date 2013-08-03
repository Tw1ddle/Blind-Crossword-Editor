#include "aboutpage.h"
#include "ui_aboutpage.h"

#include "appinfo.h"

#include "contributorspage.h"
#include "licensepage.h"

#include <memory>

namespace AppInfo
{

AboutPage::AboutPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutPage)
{
    ui->setupUi(this);

    QString appName = getAppName();

    setWindowTitle(tr("About"));

    ui->appName->setText(appName + " " + getVersionNumber());
    ui->appDescription->setText(getAppDescription());
    ui->copyrightMessage->setText(getCopyrightNotice());
    ui->technicalDetail->setText(tr("Built with %1 and Qt %2").arg(getCompilerName()).arg(getQtVersion()));
}

AboutPage::~AboutPage()
{
    delete ui;
}

void AboutPage::showLicensePage()
{
    LicensePage licensePage;

    licensePage.exec();
}

void AboutPage::showContributorsPage()
{
    ContributorsPage contributorsPage;

    contributorsPage.exec();
}

}
