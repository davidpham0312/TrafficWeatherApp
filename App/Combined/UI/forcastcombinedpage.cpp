#include "forcastcombinedpage.h"
#include "ui_forcastcombinedpage.h"

forcastCombinedPage::forcastCombinedPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::forcastCombinedPage)
{
    ui->setupUi(this);
}

forcastCombinedPage::~forcastCombinedPage()
{
    delete ui;
}
