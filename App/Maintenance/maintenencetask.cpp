#include "maintenencetask.h"

int MaintenenceTask::getId() const
{
    return id;
}

void MaintenenceTask::setId(int newId)
{
    id = newId;
}

int MaintenenceTask::getPrevId() const
{
    return prevId;
}

void MaintenenceTask::setPrevId(int newPrevId)
{
    prevId = newPrevId;
}

const QString &MaintenenceTask::getType() const
{
    return type;
}

void MaintenenceTask::setType(const QString &newType)
{
    type = newType;
}

const QDateTime &MaintenenceTask::getStartTime() const
{
    return startTime;
}

void MaintenenceTask::setStartTime(const QDateTime &newStartTime)
{
    startTime = newStartTime;
}

const QDateTime &MaintenenceTask::getEndTime() const
{
    return endTime;
}

void MaintenenceTask::setEndTime(const QDateTime &newEndTime)
{
    endTime = newEndTime;
}

int MaintenenceTask::getDirection() const
{
    return direction;
}

void MaintenenceTask::setDirection(int newDirection)
{
    direction = newDirection;
}

const QString &MaintenenceTask::getDomain() const
{
    return domain;
}

void MaintenenceTask::setDomain(const QString &newDomain)
{
    domain = newDomain;
}

const QString &MaintenenceTask::getSource() const
{
    return source;
}

void MaintenenceTask::setSource(const QString &newSource)
{
    source = newSource;
}

MaintenenceTask::MaintenenceTask()
{

}
