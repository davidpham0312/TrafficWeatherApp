#include "forecastcardwidget.h"
#include "ui_forecastcardwidget.h"

ForecastCardWidget::ForecastCardWidget(QString type, double airTemp, double roadTemp,
                                       QString forecastName, QString condition, bool daylight,
                                       double windSpeed, double windDir, QString reliability,
                                       QString symbol, ForecastConditionReason allReasons, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ForecastCardWidget) , type_{type}, airTemp_{airTemp}, roadTemp_{roadTemp}
    , forecastName_{forecastName}, condition_{condition}, daylight_{daylight}
    , windSpeed_{windSpeed}, windDir_{windDir}, reliability_{reliability}
    , symbol_{symbol}, allReasons_{allReasons}
{
    ui->setupUi(this);
    setCardAlignment();
}

ForecastCardWidget::~ForecastCardWidget()
{
    delete ui;
}

void ForecastCardWidget::addDataToCard()
{
    ui->airTempValue->setText(QString::number(airTemp_) + "˚C");
    ui->roadTempValue->setText(QString::number(roadTemp_) + "˚C");
    ui->roadCondValue->setText(condition_.replace('_', ' ').toLower());
    ui->daylightValue->setText(daylight_ == 0 ? "true" : "false");
    ui->windSpeedValue->setText(QString::number(windSpeed_) + " m/s");
    ui->windDirValue->setText(QString::number(windDir_) + "˚");
    ui->reliabilityValue->setText(reliability_.replace('_', ' ').toLower());
    ui->symbolValue->setText(symbol_);
}

void ForecastCardWidget::addCurrentDataToCard(){

    addDataToCard();
    showOrHideReasons();
    this->setStyleSheet(".QWidget, .QLabel {background-color: #94cbf2;}");
}

void ForecastCardWidget::addComparingDataToCard(){
    addDataToCard();
    showOrHideReasons();
    this->setStyleSheet(".QWidget, .QLabel {background-color: #FFE3C9;}");
}

void ForecastCardWidget::showOrHideReasons(){
    QString windCondition = allReasons_.getWindCondition();
    QString freezeRainCondition = QString::number(allReasons_.getFreezingRainCondition());
    QString frictionCondition = allReasons_.getFrictionCondition();
    QString precipitationCondition = allReasons_.getPrecipitationCondition();
    QString roadCondition = allReasons_.getRoadCondition();
    QString visibilityCondition = allReasons_.getVisibilityCondition();
    QString winterSlipperiness = QString::number(allReasons_.getWinterSlipperiness());
    if (!windCondition.isEmpty()){
        ui->windWidget->show();
        ui->windReasonValue->setText(windCondition);
    }
    else{
        ui->windWidget->hide();
    }
    if (!freezeRainCondition.isEmpty()){
        ui->freezeRainWidget->show();
        ui->freezeRainValue->setText(freezeRainCondition);
    }
    else{
        ui->freezeRainWidget->hide();
    }
    if (!frictionCondition.isEmpty()){
        ui->frictionWidget->show();
        ui->frictionValue->setText(frictionCondition);
    }
    else{
        ui->frictionWidget->hide();
    }
    if (!precipitationCondition.isEmpty()){
        ui->precipitationWidget->show();
        ui->precipitationValue->setText(precipitationCondition.replace('_', ' ').toLower());
    }
    else{
        ui->precipitationWidget->hide();
    }
    if (!roadCondition.isEmpty()){
        ui->roadWidget->show();
        ui->roadValue->setText(roadCondition.replace('_', ' ').toLower());
    }
    else{
        ui->roadWidget->hide();
    }
    if (!visibilityCondition.isEmpty()){
        ui->visibilityWidget->show();
        ui->visibilityValue->setText(visibilityCondition);
    }
    else{
        ui->visibilityWidget->hide();
    }
    if (!winterSlipperiness.isEmpty()){
        ui->slipperinessWidget->show();
        ui->slipperinessValue->setText(winterSlipperiness);
    }
    else{
        ui->slipperinessWidget->hide();
    }
}

void ForecastCardWidget::hideDefaultCards(){
    ui->forecastReasonCard->hide();
    ui->reliabilityCard->hide();
    ui->daylightCard->hide();
    ui->symbolCard->hide();
    ui->roadCondCard->hide();

    ui->windWidget->hide();
    ui->roadWidget->hide();
    ui->frictionWidget->hide();
    ui->precipitationWidget->hide();
    ui->slipperinessWidget->hide();
    ui->freezeRainWidget->hide();
    ui->visibilityWidget->hide();
}

void ForecastCardWidget::setCardAlignment(){
    ui->leftColLayout->setAlignment(Qt::AlignTop);
    ui->midColLayout->setAlignment(Qt::AlignTop);
    ui->forecastReasonLayout->setAlignment(Qt::AlignTop);
}

QWidget *ForecastCardWidget::getRoadTempCard(){
    return ui->roadTempCard;
}

QWidget *ForecastCardWidget::getAirTempCard(){
    return ui->airTempCard;
}

QWidget *ForecastCardWidget::getRoadCondCard(){
    return ui->roadCondCard;
}

QWidget *ForecastCardWidget::getDaylightCard(){
    return ui->daylightCard;
}

QWidget *ForecastCardWidget::getWindSpeedCard(){
    return ui->windSpeedCard;
}

QWidget *ForecastCardWidget::getWindDirCard(){
    return ui->windDirCard;
}

QWidget *ForecastCardWidget::getReliabilityCard(){
    return ui->reliabilityCard;
}

QWidget *ForecastCardWidget::getSymbolCard(){
    return ui->symbolCard;
}

QWidget *ForecastCardWidget::getReasonCard(){
    return ui->forecastReasonCard;
}
