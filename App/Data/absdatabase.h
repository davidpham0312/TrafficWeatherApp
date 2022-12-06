#ifndef ABSDATABASE_H
#define ABSDATABASE_H

#include <QString>
#include <QFile>
#include <QDir>

class AbsDataBase
{
public:
    AbsDataBase(); //TODO: make this as a signleton
    virtual QStringList getStoredFilesList();
protected:
    // copies a temp file into database folder. getTempFilePath() > gethDbPath()/filename
    bool dbStore(QString filename);
    bool dbStore(QString filename, QString extension);
    bool dbStore(QString filename, QByteArray data);
    // loads a file from the specified database into the bytearray 'doc'
    void dbLoad(QString filename, QByteArray& doc);

    //this returns the list of all files in the database

    // abstract function that return the appropriate database path
    // must be supplied by concrete db classes
    virtual QString getDbPath() = 0;
    // abstract function that return the appropriate temp path
    virtual QString getTempPath() = 0;
    // abstract function that return the appropriate temp file name
    virtual QString getTempFile() = 0;
};

#endif // ABSDATABASE_H
