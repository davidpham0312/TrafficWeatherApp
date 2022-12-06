#include "absdatabase.h"

AbsDataBase::AbsDataBase()
{

}

bool AbsDataBase::dbStore(QString filename)
{
   return dbStore(filename,QString(""));
}

bool AbsDataBase::dbStore(QString filename, QString extension)
{
    QDir().mkpath(getDbPath());
    QDir().mkpath(getTempPath());
    QString src = getTempPath().append(getTempFile()).append(extension);
    QString dest = getDbPath().append(filename).append(extension);
    QFile destFile(dest);
    if(destFile.exists()) destFile.remove();
    return QFile::copy(src, dest);
}

bool AbsDataBase::dbStore(QString filename, QByteArray data)
{
    QDir().mkpath(getDbPath());

    //save the reply to a json file
    QFile file(getDbPath().append(filename));
    file.remove();
    if(file.open(QIODevice::ReadWrite)){
        file.write(data);
        file.close();
        return true;
    }else {
        return false;
    }
}



void AbsDataBase::dbLoad(QString filename, QByteArray &doc)
{
    QFile file(getDbPath().append(filename));
    if(file.open(QIODevice::ReadOnly)){
        doc = file.readAll();
    }
    file.close();

}


QStringList AbsDataBase::getStoredFilesList()
{
    QDir directory(getDbPath());
    QStringList list = directory.entryList(QDir::Files);
    return list;
}


