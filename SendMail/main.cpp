#include <QCoreApplication>
#include "database.h"
#include "sendmailclass.h"
#include <unistd.h>

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
    QCoreApplication a(argc, argv);

    DBManager d1("//Users//Ben//Dropbox//cs3380//FP.db");

    QSqlQuery query;//query to select time
    QSqlQuery query1;//query to select pawprint
    QSqlQuery query2;//query to select ItemName
    QSqlQuery query3;//query to select BorrowTime
    QSqlQuery query4;//query to select ReturnTime
    vector <int> TimeList;
    vector <string> PawPrintList;
    vector <string> ItemNameList;
    vector <string> BorrowTimeList;
    vector <string> ReturnTimeList;
    vector <bool> MailFlagList;

    while(1){
        unsigned long i = 0;
        //reset the vectors everytime to store new values
        TimeList.clear();
        PawPrintList.clear();
        ItemNameList.clear();
        BorrowTimeList.clear();
        ReturnTimeList.clear();
        MailFlagList.clear();

        query.exec("SELECT julianday('now','localtime')*1440 - julianday(BorrowTime)*1440 From Item where Status = 0;");
        query1.exec("SELECT PawPrint from Item where Status = 0;");
        query2.exec("SELECT ItemName from Item where Status = 0;");
        query3.exec("SELECT BorrowTime from Item where Status = 0;");
        query4.exec("SELECT ReturnTime from Item where Status = 0;");

        while(query.next()){
            int time = query.value(0).toInt();
            TimeList.push_back(time);
            MailFlagList.push_back(false);
        }
        while(query1.next()){
            QString PawPrint = query1.value(0).toString();
            PawPrintList.push_back(PawPrint.toStdString());
        }
        while(query2.next()){
            QString ItemName = query2.value(0).toString();
            ItemNameList.push_back(ItemName.toStdString());
        }
        while(query3.next()){
            QString BorrowTime = query3.value(0).toString();
            BorrowTimeList.push_back(BorrowTime.toStdString());
        }
        while(query4.next()){
            QString ReturnTime = query4.value(0).toString();
            ReturnTimeList.push_back(ReturnTime.toStdString());
        }


        while( i < TimeList.size()){
            cout << TimeList[i] << endl;
            if(TimeList[i] <= 60 && MailFlagList[i] == false){
                //write email here

                string SentMailCommand = "echo \" Dear Student, \n  You have borrwed " + ItemNameList[i]
                        + " in " + BorrowTimeList[i] +  ". It has to be returned by " + ReturnTimeList[i] +  ", Please return it in time to avoid charge.\nMizzou Checkout\""
                          " | mail -s \"Item return notice\" \" " + PawPrintList[i] + "@mail.missouri.edu\"";
                QProcess *process = new QProcess;
                const char *SentMailCommandInChar = SentMailCommand.c_str();
                process->start("bash" );
                process->write(SentMailCommandInChar);
                MailFlagList[i] = true;
                //test output
                cout << SentMailCommand;
                cout << "---------------------------------" << endl;


            }
            i++;



        }
        usleep(1000);
    }
    return a.exec();
}
