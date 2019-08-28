#include "mainwindow.h"
#include <QApplication>
#include "loginwindow.h"
#include "signupwindow.h"
#include "database.h"
#include <QDir>
DBManager::DBManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

void DBManager::CreateUser(const QString &Pawprint, const QString &Name, const int StudentId, const int UserType, const QString &Password)
{
    QSqlQuery query;
//    query.prepare("INSERT INTO User (Pawprint, Name, StudentId, UserType, Password) "
//                  "values(:Pawprint, :Name, :StudentId, :UserType, :Password)");
    query.prepare("UPDATE User SET Pawprint = :Pawprint, Name = :Name, UserType = :UserType, Password = :Password WHERE StudentId = :StudentId");

    query.bindValue(":Pawprint", Pawprint);
    query.bindValue(":Name", Name);
    query.bindValue(":StudentId", StudentId);
    query.bindValue(":UserType", UserType);
    query.bindValue(":Password", Password);

    if(query.exec())
    {
        cout<<"insert success!!"<<endl;
    }
    else
    {
        qDebug()<<"error" << query.lastError();
    }
}

int DBManager::check(const QString &Pawprint, const QString &Password)
{
    QSqlQuery query;
    query.prepare("SELECT Pawprint, Password FROM User WHERE Pawprint = (:Pawprint)"
                  "and Password = (:Password)");
    query.bindValue(":Pawprint",Pawprint);
    query.bindValue(":Password",Password);
    if(query.exec())
    {
        if(query.next())
        {
            cout<<"logged in"<<endl;
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int DBManager::check(int StudentID)
{
    QSqlQuery query;
    query.prepare("SELECT StudentId FROM User WHERE StudentId = (:StudentId)");
    query.bindValue(":StudentId",StudentID);
    if(query.exec())
    {
        if(query.next())
        {
            cout<<"ID matched."<<endl;
            return 1;
        }
    }
    else
    {
        return -1;
    }
}

int DBManager::getUserType(QString PawPrint){
    int ID = 0;//if is admin
    QSqlQuery query;
    query.prepare("SELECT UserType FROM User WHERE UserType = (:UserType) AND PawPrint = (:PawPrint)");
    query.bindValue(":UserType",ID);
    query.bindValue(":PawPrint",PawPrint);
    if(query.exec())
    {
        if(query.next())
        {
            cout<<"Admin found."<<endl;
            return 0;
        }
    }
    else
    {
        return 1;
    }

}
void DBManager::InsertItem(const int ItemId, const QString &ItemName, const QString &Location, const int BorrowLength){

    QSqlQuery query;
    query.prepare("INSERT INTO Item (ItemId, ItemName, Status, Location, BorrowLength) "
                  "values(:ItemId, :ItemName, :Status, :Location, :BorrowLength)");


    query.bindValue(":ItemId", ItemId);
    query.bindValue(":ItemName", ItemName);
    query.bindValue(":Status", 1);
    query.bindValue(":Location", Location);
    query.bindValue(":BorrowLength", BorrowLength);

    //need error handling
    if(query.exec())
    {
        cout<<"insert Item success!!"<<endl;
    }
    else
    {
        qDebug()<<"error" << query.lastError();
    }

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString FileLocation = QDir::homePath() + "//Dropbox//cs3380//FP.db";
    DBManager d1(FileLocation);

  //  qDebug() <<  QDir::homePath();
    LoginWindow lw;
    lw.data = &d1;
    lw.show();

    return a.exec();
}
