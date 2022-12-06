#ifndef MAINTENENCETASK_H
#define MAINTENENCETASK_H

#include <QDateTime>

class MaintenenceTask
{

private:
    int id;
    int prevId;
    QString type;
    QDateTime startTime;
    QDateTime endTime;
    int direction;
    QString domain;
    QString source;

public:
    MaintenenceTask();
    int getId() const;
    void setId(int newId);
    int getPrevId() const;
    void setPrevId(int newPrevId);
    const QString &getType() const;
    void setType(const QString &newType);
    const QDateTime &getStartTime() const;
    void setStartTime(const QDateTime &newStartTime);
    const QDateTime &getEndTime() const;
    void setEndTime(const QDateTime &newEndTime);
    int getDirection() const;
    void setDirection(int newDirection);
    const QString &getDomain() const;
    void setDomain(const QString &newDomain);
    const QString &getSource() const;
    void setSource(const QString &newSource);
};



#endif // MAINTENENCETASK_H
