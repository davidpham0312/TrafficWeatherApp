#include "messagecardwidget.h"
#include "ui_messagecardwidget.h"

MessageCardWidget::MessageCardWidget(QString title, QString comment, QString location,
                                     QList<QString> features, QDateTime startTime, QDateTime endTime,
                                     QString email, QString number,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MessageCardWidget)
    , title_{title}
    , comment_{comment}
    , location_{location}
    , features_{features}
    , startTime_{startTime}
    , endTime_{endTime}
    , email_{email}
    , number_{number}
{
    ui->setupUi(this);
}

MessageCardWidget::~MessageCardWidget()
{
    delete ui;
}

void MessageCardWidget::addCurrentDataToCard(){

    ui->titleOutput->setText(title_);
    ui->commentOutput->setText(comment_);
    ui->locationOutput->setText(location_);

    ui->startTimeOutput->setText(startTime_.toString());
    ui->endTimeOutput->setText(endTime_.toString());
    ui->emailOutput->setText(email_);
    ui->numberOutput->setText(number_);
    for (auto &f : features_){
        ui->featuresOutput->setText(ui->featuresOutput->text()
                                    + (ui->featuresOutput->text().isEmpty() ? "" : "\n")
                                    + f);
    }
    ui->frame->setStyleSheet("background-color: #E8E8E8;"
                             "color: black;"
                             "border-radius: 20px");

    ui->frame->setFixedWidth(400);
}

void MessageCardWidget::addComparingDataToCard(){

    ui->titleOutput->setText(title_);
    ui->commentOutput->setText(comment_);
    ui->locationOutput->setText(location_);

    ui->startTimeOutput->setText(startTime_.toString());
    ui->endTimeOutput->setText(endTime_.toString());
    ui->emailOutput->setText(email_);
    ui->numberOutput->setText(number_);
    for (auto &f : features_){
        ui->featuresOutput->setText(ui->featuresOutput->text()
                                    + (ui->featuresOutput->text().isEmpty() ? "" : "\n")
                                    + f);
    }
    ui->frame->setStyleSheet("background-color: #FFE3C9;"
                             "color: black;"
                             "border-radius: 20px");

    ui->frame->setFixedWidth(400);
}

