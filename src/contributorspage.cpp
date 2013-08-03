#include "contributorspage.h"
#include "ui_contributorspage.h"

#include "appinfo.h"

namespace AppInfo
{

ContributorsPage::ContributorsPage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ContributorsPage)
{   
    ui->setupUi(this);

    ui->programmerText->setText(AppInfo::getProgrammers());
    ui->translatorText->setText(AppInfo::getTranslators());
    ui->artworkText->setText(AppInfo::getArtists());
}

ContributorsPage::~ContributorsPage()
{
    delete ui;
}

}
