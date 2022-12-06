QT       += core gui charts network svgwidgets
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Combined/UI/combinedview.cpp \
    Data/absdatabase.cpp \
    Data/appdatabase.cpp \
    Data/httpclient.cpp \
    Data/location.cpp \
    Dialogs/filepickerdialog.cpp \
    Dialogs/locationdialog.cpp \
    Dialogs/savefiledialog.cpp \
    Forecast/UI/Model/forecastclient.cpp \
    Forecast/UI/Model/forecastdatabase.cpp \
    Forecast/UI/Model/forecastrepository.cpp \
    Forecast/UI/forecastcardwidget.cpp \
    Forecast/UI/forecastcharthelper.cpp \
    Forecast/UI/forecastview.cpp \
    Forecast/forecastparams.cpp \
    Forecast/json2forecastlist.cpp \
    Maintenance/UI/Model/maintenanceclient.cpp \
    Maintenance/UI/Model/maintenancedatabase.cpp \
    Maintenance/UI/Model/maintenancerepository.cpp \
    Maintenance/UI/Model/json2maintenancedata.cpp \
    Maintenance/UI/maintenancecharthelper.cpp \
    Maintenance/UI/maintenanceview.cpp \
    Maintenance/maintenancedata.cpp \
    Messages/UI/Model/messagesrepository.cpp \
    Messages/UI/Model/messagesdatabase.cpp \
    Messages/UI/Model/messagesclient.cpp \
    Messages/UI/Model/json2messagelist.cpp \
    Messages/UI/messagecardwidget.cpp \
    Messages/UI/messagescontroller.cpp \
    Messages/UI/messagesview.cpp \
    Weather/UI/Model/weatherclient.cpp \
    Weather/UI/Model/weatherdatabase.cpp \
    Weather/UI/Model/weatherforecastdata.cpp \
    Weather/UI/Model/weatherobservationdata.cpp \
    Weather/UI/Model/weatherrepository.cpp \
    Weather/UI/Model/xml2weatherdataconverter.cpp \
    Weather/UI/Model/xml2weatherforecast.cpp \
    Weather/UI/Model/xml2weatherobservation.cpp \
    Weather/UI/weathercontroller.cpp \
    Weather/UI/weatherview.cpp \
    Weather/weatherparams.cpp \
    main.cpp \
    mainwindow.cpp \
    Messages/messagesparams.cpp \
    Messages/message.cpp \
    Maintenance/maintenanceparams.cpp \
    Forecast/forecastdatasample.cpp \
    Forecast/UI/forecastcontroller.cpp \
    Maintenance/UI/maintenancecontroller.cpp \
    Dialogs/waitdialog.cpp \
    weathercharthelper.cpp


HEADERS += \
    Combined/UI/combinedview.h \
    Data/absdatabase.h \
    Data/appdatabase.h \
    Data/db_paths.h \
    Data/httpclient.h \
    Data/location.h \
    Dialogs/filepickerdialog.h \
    Dialogs/locationdialog.h \
    Dialogs/savefiledialog.h \
    Forecast/UI/Model/forecastclient.h \
    Forecast/UI/Model/forecastdatabase.h \
    Forecast/UI/Model/forecastrepository.h \
    Forecast/UI/forecastcardwidget.h \
    Forecast/UI/forecastcharthelper.h \
    Forecast/UI/forecastview.h \
    Forecast/forecastcallbacks.h \
    Forecast/forecastparams.h \
    Forecast/json2forecastlist.h \
    Maintenance/UI/Model/maintenanceclient.h \
    Maintenance/UI/Model/maintenancerepository.h \
    Maintenance/UI/Model/json2maintenancedata.h \
    Maintenance/UI/maintenancecharthelper.h \
    Maintenance/UI/maintenanceview.h \
    Maintenance/maintenancedata.h \
    Messages/UI/messagecardwidget.h \
    Messages/UI/messagescontroller.h \
    Messages/UI/Model/messagesrepository.h \
    Messages/UI/Model/messagesdatabase.h \
    Messages/UI/Model/messagesclient.h \
    Messages/UI/Model/json2messagelist.h \
    Messages/UI/messagesview.h \
    Weather/UI/Model/weatherclient.h \
    Weather/UI/Model/weatherdatabase.h \
    Weather/UI/Model/weatherforecastdata.h \
    Weather/UI/Model/weatherobservationdata.h \
    Weather/UI/Model/weatherrepository.h \
    Weather/UI/Model/xml2weatherdataconverter.h \
    Weather/UI/Model/xml2weatherforecast.h \
    Weather/UI/Model/xml2weatherobservation.h \
    Weather/UI/weathercontroller.h \
    Weather/UI/weatherview.h \
    Weather/weathercallbacks.h \
    Weather/weatherparams.h \
    mainwindow.h \
    Messages/messagesparams.h \
    Messages/MessagesCallbacks.h\
    Messages/message.h \
    Maintenance/maintenanceparams.h \
    Maintenance/maintenancecallbacks.h \
    Forecast/forecastdatasample.h \
    Forecast/UI/forecastcontroller.h \
    Maintenance/UI/maintenancecontroller.h \
    Dialogs/waitdialog.h \
    weathercharthelper.h


FORMS += \
    Combined/UI/combinedview.ui \
    Dialogs/filepickerdialog.ui \
    Dialogs/locationdialog.ui \
    Dialogs/savefiledialog.ui \
    Forecast/UI/forecastcardwidget.ui \
    Forecast/UI/forecastview.ui \
    Maintenance/UI/maintenanceview.ui \
    Messages/UI/messagecardwidget.ui \
    Messages/UI/messagesview.ui \
    Weather/UI/weatherview.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

