#include "mainwindow.h"
#include "Messages/UI/messagesview.h"
#include "Messages/UI/messagescontroller.h"
#include <Weather/UI/weatherview.h>
#include <Weather/UI/weathercontroller.h>
#include <QApplication>
#include <Data/absdatabase.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;


    //prefill locations for the first time
    AppDatabase::getInstance().prefillLocations();

    // MVC connection for messages
    MessagesRepository msgRepo(&w);
    MessagesView *msgWindow = w.getMsgWindow();
    MessagesController *msgController{new MessagesController(msgRepo, msgWindow, &w)};
    msgWindow->setController(msgController);

    // MVC connection for road forecast (the view now is responsible for creating the controller)
    // ForecastRepository forecastRepo(&w);
    // ForecastView *forecastWindow = w.getForecastWindow();
    // ForecastController *forecastController{new ForecastController(forecastWindow, &w)};
    // forecastWindow->setController(forecastController);


    // MVC connection for weather
    WeatherRepository weatherRepo(&w);
    WeatherView *weatherWindow = w.getWeatherWindow();
    WeatherController *weatherController{new WeatherController(weatherRepo, weatherWindow, &w)};
    weatherWindow->setController(weatherController);
    w.show();


    return a.exec();
}
