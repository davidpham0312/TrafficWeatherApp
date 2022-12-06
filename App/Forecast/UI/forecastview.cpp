#include "forecastview.h"
#include "forecastcharthelper.h"
#include "ui_forecastview.h"
#include "Forecast/UI/forecastcontroller.h"
#include "Dialogs/savefiledialog.h"

ForecastView::ForecastView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ForecastView)
//    , forecastController_{nullptr}
{
    ui->setupUi(this);
    hideAllLayouts();
    locations = AppDatabase::getInstance().getLocationsList();
    ui->savedDropdown->addItems(locations.keys());
    waitingDialog = new WaitDialog(this);
    forecastController_ = new ForecastController(this, this);
}

ForecastView::~ForecastView()
{
    delete ui;
}

ForecastDataSample ForecastView::selectDisplayData(QString hours, QList<ForecastDataSample> forecastDataList){
    if (hours.compare("0 hour")){
        return forecastDataList.at(0);
    }
    else if (hours.compare("2 hours")){
        return forecastDataList.at(1);
    }
    else if (hours.compare("4 hours")){
        return forecastDataList.at(2);
    }
    else if (hours.compare("6 hours")){
        return forecastDataList.at(3);
    }
    else {
        return forecastDataList.at(4);
    }
}

void ForecastView::displayCurrentForecastCard(QList<ForecastDataSample> allForecastData){
    emptyFrame(ui->currentCardFrame);
    emptyFrame(ui->compareCardFrame);
    ForecastDataSample s = selectDisplayData(ui->timeDropdown->currentText(), allForecastData);
    currentCard = getCardWidget(s);
    currentCard->addCurrentDataToCard();
    ui->currentCardLayout->addWidget(currentCard);
    ui->currentCardFrame->show();
    ui->showAllRButton->click();
}

void ForecastView::displayComparingForecastCard(QList<ForecastDataSample> allForecastData){
    emptyFrame(ui->compareCardFrame);

    ForecastDataSample s = selectDisplayData(ui->timeDropdown->currentText(), allForecastData);
    comparingCard = getCardWidget(s);
    comparingCard->addComparingDataToCard();
    ui->compareCardLayout->addWidget(comparingCard, 0, Qt::AlignTop);
    ui->compareCardFrame->show();
    ui->showAllRButton->click();
}

void ForecastView::displayCurrentForecastGraphs(QList<ForecastDataSample> allForecastData){
    setCurrentRoadAirDataPoint(allForecastData);
    setCurrentWindDataPoint(allForecastData);
    displayRoadAirChart();
    displayWindChart();
}

void ForecastView::displayComparingForecastGraphs(QList<ForecastDataSample> allForecastData){
    setComparingRoadAirDataPoint(allForecastData);
    setComparingWindDataPoint(allForecastData);
    displayRoadAirChart();
    displayWindChart();
}

ForecastCardWidget *ForecastView::getCardWidget(ForecastDataSample s){
    return new ForecastCardWidget(s.getType(), s.getAirTemp(), s.getRoadTemp(),
                                  s.getForecastName(), s.getOverallRoadCondition(),
                                  s.getDaylight(), s.getWindSpeed(), s.getWindDirection(),
                                  s.getReliability(), s.getWeatherSymbol(),
                                  s.getForecastReason(), this);
}

void ForecastView::setCurrentRoadAirDataPoint(QList<ForecastDataSample> allData){
    if (!roadAirData.isEmpty()){
        roadAirData.clear();
    }
    QMap<double, double> roadData{{0, allData.at(0).getRoadTemp()},
                                  {2, allData.at(1).getRoadTemp()},
                                  {4, allData.at(2).getRoadTemp()},
                                  {6, allData.at(3).getRoadTemp()},
                                  {12, allData.at(4).getRoadTemp()}};

    QMap<double, double> airData{{0, allData.at(0).getAirTemp()},
                                 {2, allData.at(1).getAirTemp()},
                                 {4, allData.at(2).getAirTemp()},
                                 {6, allData.at(3).getAirTemp()},
                                 {12, allData.at(4).getAirTemp()}};
    roadAirData.append(roadData);
    roadAirData.append(airData);
}

void ForecastView::setCurrentWindDataPoint(QList<ForecastDataSample> allData){
    if (!windSpeedData.isEmpty()){
        windSpeedData.clear();
    }
    if (!windDirData.isEmpty()){
        windDirData.clear();
    }
    QMap<double, double> speedData{{0, allData.at(0).getWindSpeed()},
                                   {2, allData.at(1).getWindSpeed()},
                                   {4, allData.at(2).getWindSpeed()},
                                   {6, allData.at(3).getWindSpeed()},
                                   {12, allData.at(4).getWindSpeed()}};

    QMap<double, double> dirData{{0, allData.at(0).getWindDirection()},
                                 {2, allData.at(1).getWindDirection()},
                                 {4, allData.at(2).getWindDirection()},
                                 {6, allData.at(3).getWindDirection()},
                                 {12, allData.at(4).getWindDirection()}};
    windSpeedData.append(speedData);
    windDirData.append(dirData);
}

void ForecastView::setComparingRoadAirDataPoint(QList<ForecastDataSample> allData){
    QMap<double, double> roadData{{0, allData.at(0).getRoadTemp()},
                                  {2, allData.at(1).getRoadTemp()},
                                  {4, allData.at(2).getRoadTemp()},
                                  {6, allData.at(3).getRoadTemp()},
                                  {12, allData.at(4).getRoadTemp()}};

    QMap<double, double> airData{{0, allData.at(0).getAirTemp()},
                                 {2, allData.at(1).getAirTemp()},
                                 {4, allData.at(2).getAirTemp()},
                                 {6, allData.at(3).getAirTemp()},
                                 {12, allData.at(4).getAirTemp()}};
    if (roadAirData.size() == 4){
        roadAirData[2] = roadData;
        roadAirData[3] = airData;
    }
    else{
        roadAirData.append(roadData);
        roadAirData.append(airData);
    }
}

void ForecastView::setComparingWindDataPoint(QList<ForecastDataSample> allData){
    QMap<double, double> speedData{{0, allData.at(0).getWindSpeed()},
                                       {2, allData.at(1).getWindSpeed()},
                                       {4, allData.at(2).getWindSpeed()},
                                       {6, allData.at(3).getWindSpeed()},
                                       {12, allData.at(4).getWindSpeed()}};

    QMap<double, double> dirData{{0, allData.at(0).getWindDirection()},
                                     {2, allData.at(1).getWindDirection()},
                                     {4, allData.at(2).getWindDirection()},
                                     {6, allData.at(3).getWindDirection()},
                                     {12, allData.at(4).getWindDirection()}};
    if (windDirData.size() == 2 && windSpeedData.size() == 2){
        windDirData.back() = dirData;
        windSpeedData.back() = speedData;
    }
    else{
        windSpeedData.append(speedData);
        windDirData.append(dirData);
    }

}

void ForecastView::displayRoadAirChart(){
    emptyFrame(ui->airRoadFrame);
    ForecastChartHelper *chart = new ForecastChartHelper(this);
    QVector<QString> roadAirLegends({"Current road temperature (º)", "Current air temperature (º)",
                                     "Comparing road temperature (º)", "Comparing air temperature (º)"});
    chart->displayData(roadAirData, roadAirLegends, "Road and air temperature",
                       "Hours (h)", "Temperature (ºC)");
    tempChart = chart;
    ui->airRoadGraph->addWidget(chart);
    ui->airRoadFrame->show();
}

void ForecastView::displayWindChart(){
    emptyFrame(ui->windSpeedFrame);
    ForecastChartHelper *chart = new ForecastChartHelper(this);
    QVector<QString> speedLegends({"Current wind speed (m/s)", "Comparing wind speed (m/s)"});
    QVector<QString> directionLegends({"Current wind direction (º)", "Comparing wind direction (º)"});
    chart->displayDataWithTwoYAxes(windSpeedData, speedLegends, windDirData,
                                   directionLegends, "Wind speed and wind direction",
                                   "Hours (h)", "Speed (m/s)", "Direction (º)");
    windChart = chart;
    ui->windSpeedDirGraph->addWidget(chart);
    ui->windSpeedFrame->show();
}

void ForecastView::hideAllLayouts(){
    ui->saveTempButton->setVisible(false);
    ui->saveWindButton->setVisible(false);
    ui->forecastSaveSuccessNoti->hide();
    ui->forecastTitleLabel->hide();
    ui->currentCardFrame->hide();
    ui->compareCardFrame->hide();
    ui->windSpeedFrame->hide();
    ui->airRoadFrame->hide();
    ui->textPreview->show();
}

void ForecastView::emptyFrame(QFrame *frame){
    QLayoutItem* item;
    while ( ( item = frame->layout()->takeAt( 0 ) ) != NULL )
    {
        delete item->widget();
        delete item;
    }
}

void ForecastView::saveUserInput()
{
    currentParams.setMaxLatitude(ui->xMax->text().toDouble());
    currentParams.setMaxLongitude(ui->yMax->text().toDouble());
    currentParams.setMinLatitude(ui->xMin->text().toDouble());
    currentParams.setMinLongitude(ui->yMin->text().toDouble());
    AppDatabase::getInstance().storeForecastSettings(currentParams);
}

void ForecastView::restoreUserInput()
{
    ForecastParams params = AppDatabase::getInstance().restoreForecastSettings();
    ui->xMax->setText(QString("%1").arg(params.getMaxLatitude()));
    ui->yMax->setText(QString("%1").arg(params.getMaxLongitude()));
    ui->xMin->setText(QString("%1").arg(params.getMinLatitude()));
    ui->yMin->setText(QString("%1").arg(params.getMinLongitude()));
    ui->savedDropdown->setCurrentIndex(-1);
    ui->timeDropdown->setCurrentIndex(-1);
}

void ForecastView::location_added()
{
    //populate locations (not the best practice here, but what can we do !)
    locations = AppDatabase::getInstance().getLocationsList();
    ui->savedDropdown->clear(); //dont forget to clear!
    ui->savedDropdown->addItems(locations.keys());
}

void ForecastView::setController(ForecastController *forecastController){
    forecastController_ = forecastController;
}

void ForecastView::enableButtons(){
    ui->showAllRButton->setEnabled(true);
    ui->hideAllRButton->setEnabled(true);

    setEnableCheckBoxes(true);
}

void ForecastView::enableSaveButton()
{
    ui->forecastSaveDataButton->setEnabled(true);
}

void ForecastView::showTitle()
{
    ui->forecastTitleLabel->show();
}

bool ForecastView::checkInputBeforeSave(ForecastParams param)
{
    if (param.getMinLongitude() != ui->xMin->text().toDouble() ||
        param.getMaxLongitude() != ui->xMax->text().toDouble() ||
        param.getMinLatitude() != ui->yMin->text().toDouble() ||
        param.getMaxLatitude() != ui->xMax->text().toDouble()) {
        return false;
    }
    return true;
}

void ForecastView::showSaveSuccessNoti()
{
    ui->forecastSaveSuccessNoti->show();
}

void ForecastView::showSaveButton()
{
    ui->saveTempButton->show();
    ui->saveWindButton->show();
}

void ForecastView::on_forecastVisualizeButton_clicked()
{
    ui->textPreview->hide();
    if (forecastController_ != nullptr){
        forecastController_->visualizeButtonClicked(ui->xMin->text().toDouble(),
                                                    ui->yMin->text().toDouble(),
                                                    ui->xMax->text().toDouble(),
                                                    ui->yMax->text().toDouble(),
                                                    ui->timeDropdown->currentIndex());
    }
}

void ForecastView::showAlertDialog(QString message)
{
    QMessageBox msgBox;
    msgBox.setText("Error!");
    msgBox.setInformativeText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setStandardButtons(QMessageBox::Close);
    msgBox.exec();
}

void ForecastView::showWaitingDialog()
{
    waitingDialog->showDialog();
}

void ForecastView::closeWaitingDialog()
{
    waitingDialog->closeDialog();
}

void ForecastView::on_forecastSaveDataButton_clicked()
{
    forecastController_->checkUserInputs(ui->xMin->text().toDouble(),
                                         ui->xMax->text().toDouble(),
                                         ui->yMin->text().toDouble(),
                                         ui->yMax->text().toDouble());
}

void ForecastView::showSaveDataDialog()
{
    int ok;
    SaveFileDialog dialog(this,
                          "FORECAST: "+QDateTime::currentDateTime().toString());
    ok = dialog.exec();

    if (ok > 0){
        forecastController_->saveButtonClicked(dialog.getFileName());
    }

}
void ForecastView::on_forecastCompareButton_clicked()
{
    forecastController_->compareButtonClicked();
}

#include "Dialogs/filepickerdialog.h"
void ForecastView::showDataChooserDialog(QStringList &items)
{
    int ok;
    FilePickerDialog dialog(this, items);
    ok = dialog.exec();
    if(ok > 0) {
        forecastController_->requestComparingData(dialog.getSelectedFileName());
    }
}

void ForecastView::on_roadTempCheckbox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentRoadTempCard = currentCard->getRoadTempCard();
        currentRoadTempCard->setVisible(arg1);
    }
    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingRoadTempCard = comparingCard->getRoadTempCard();
        comparingRoadTempCard->setVisible(arg1);
    }
}


void ForecastView::on_airTempCheckBox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentAirTempCard = currentCard->getAirTempCard();
        currentAirTempCard->setVisible(arg1);
    }
    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingAirTempCard = comparingCard->getAirTempCard();
        comparingAirTempCard->setVisible(arg1);
    }
}


void ForecastView::on_reliabilityCheckbox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentReliabilityCard = currentCard->getReliabilityCard();
        currentReliabilityCard->setVisible(arg1);
    }
    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingReliabilityCard = comparingCard->getReliabilityCard();
        comparingReliabilityCard->setVisible(arg1);
    }
}


void ForecastView::on_windDirCheckbox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentWindDirCard = currentCard->getWindDirCard();
        currentWindDirCard->setVisible(arg1);
    }
    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingWindDirCard = comparingCard->getWindDirCard();
        comparingWindDirCard->setVisible(arg1);
    }
}


void ForecastView::on_windSpeedCheckbox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentWindSpeedCard = currentCard->getWindSpeedCard();
        currentWindSpeedCard->setVisible(arg1);
    }

    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingWindSpeedCard = comparingCard->getWindSpeedCard();
        comparingWindSpeedCard->setVisible(arg1);
    }
}


void ForecastView::on_symbolCheckbox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentSymbolCard = currentCard->getSymbolCard();
        currentSymbolCard->setVisible(arg1);
    }
    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingSymbolCard = comparingCard->getSymbolCard();
        comparingSymbolCard->setVisible(arg1);
    }
}


void ForecastView::on_daylightCheckbox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentDaylightCard = currentCard->getDaylightCard();
        currentDaylightCard->setVisible(arg1);
    }
    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingDaylightCard = comparingCard->getDaylightCard();
        comparingDaylightCard->setVisible(arg1);
    }
}


void ForecastView::on_roadCondCheckbox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentRoadCondCard = currentCard->getRoadCondCard();
        currentRoadCondCard->setVisible(arg1);
    }
    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingRoadCondCard = comparingCard->getRoadCondCard();
        comparingRoadCondCard->setVisible(arg1);
    }
}


void ForecastView::on_reasonCheckbox_stateChanged(int arg1)
{
    if (!ui->currentCardLayout->isEmpty()){
        QWidget *currentReasonCard = currentCard->getReasonCard();
        currentReasonCard->setVisible(arg1);
    }
    if (!ui->compareCardLayout->isEmpty()){
        QWidget *comparingReasonCard = comparingCard->getReasonCard();
        comparingReasonCard->setVisible(arg1);
    }
}


void ForecastView::on_showAllRButton_clicked()
{
    ui->currentCardFrame->show();
    if (ui->compareCardFrame->layout()->count() != 0){
        ui->compareCardFrame->show();
    }

    setEnableCheckBoxes(true);

    setCheckBoxesState(true);
}


void ForecastView::on_hideAllRButton_clicked()
{
    ui->currentCardFrame->hide();
    ui->compareCardFrame->hide();
    setEnableCheckBoxes(false);
}

void ForecastView::setEnableCheckBoxes(bool isEnabled){
    ui->roadTempCheckbox->setEnabled(isEnabled);
    ui->windDirCheckbox->setEnabled(isEnabled);
    ui->daylightCheckbox->setEnabled(isEnabled);
    ui->airTempCheckBox->setEnabled(isEnabled);
    ui->windSpeedCheckbox->setEnabled(isEnabled);
    ui->roadCondCheckbox->setEnabled(isEnabled);
    ui->reliabilityCheckbox->setEnabled(isEnabled);
    ui->symbolCheckbox->setEnabled(isEnabled);
    ui->reasonCheckbox->setEnabled(isEnabled);
}

void ForecastView::setCheckBoxesState(bool isChecked){
    ui->roadTempCheckbox->setChecked(isChecked);
    ui->windDirCheckbox->setChecked(isChecked);
    ui->daylightCheckbox->setChecked(isChecked);
    ui->airTempCheckBox->setChecked(isChecked);
    ui->windSpeedCheckbox->setChecked(isChecked);
    ui->roadCondCheckbox->setChecked(isChecked);
    ui->reliabilityCheckbox->setChecked(isChecked);
    ui->symbolCheckbox->setChecked(isChecked);
    ui->reasonCheckbox->setChecked(isChecked);
}


void ForecastView::on_savedDropdown_textActivated(const QString &arg1)
{
    Location loc = locations.value(arg1);
    ui->xMin->setText(QString("%1").arg(loc.xMin));
    ui->xMax->setText(QString("%1").arg(loc.xMax));
    ui->yMin->setText(QString("%1").arg(loc.yMin));
    ui->yMax->setText(QString("%1").arg(loc.yMax));
}



void ForecastView::on_closeNotiButton_clicked()
{
    ui->forecastSaveSuccessNoti->hide();
}

ForecastController *ForecastView::forecastController() const
{
    return forecastController_;
}


void ForecastView::on_saveTempButton_clicked()
{
    tempChart->saveToPng();
}


void ForecastView::on_saveWindButton_clicked()
{
    windChart->saveToPng();
}

