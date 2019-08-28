#ifndef DATABASE_H
#define DATABASE_H
#include <QCoreApplication>
#include <QtSql>
#include <QtDebug>
#include <iostream>

using namespace std;

class DBManager
{
public:
    DBManager(const QString& path);
    void CreateUser(const QString& Pawprint,const QString& Name,const int StudentId, const int UserType,const QString& Password);
    int check(const QString& Pawprint, const QString& Password);
    int check(int StudentID);
    int getUserType(QString StudentID);
    void InsertItem(const int ItemId, const QString& ItemName, const QString& Location, const int BorrowLength);

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
