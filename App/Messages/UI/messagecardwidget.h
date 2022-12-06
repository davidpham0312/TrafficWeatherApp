#ifndef MESSAGECARDWIDGET_H
#define MESSAGECARDWIDGET_H

#include <QDateTime>
#include <QWidget>

namespace Ui {
class MessageCardWidget;
}

class MessageCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MessageCardWidget(QString title, QString comment, QString location,
                               QList<QString> features, QDateTime startTime, QDateTime endTime,
                               QString email, QString number,QWidget *parent = nullptr);
    ~MessageCardWidget();
    void addCurrentDataToCard();
    void addComparingDataToCard();

private:
    Ui::MessageCardWidget *ui;
    QString title_;
    QString comment_;
    QString location_;
    QList<QString> features_;
    QDateTime startTime_;
    QDateTime endTime_;
    QString email_;
    QString number_;
};

#endif // MESSAGECARDWIDGET_H
