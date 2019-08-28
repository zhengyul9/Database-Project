#include "sendmail.h"
#include <QtCore>
#include "vector"
#include "string"
#include "iostream"
#include <QDebug>
#include <QProcess>
#include <QtSql>
using namespace std;
SendMail::SendMail(QObject *parent) : QThread(parent)
{

}

void SendMail::run(){

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


//    query.exec("SELECT julianday('now','localtime')*1440 - julianday(BorrowTime)*1440 From Item where Status = 0;");
//    query1.exec("SELECT PawPrint from Item where Status = 0;");
//    query2.exec("SELECT ItemName from Item where Status = 0;");
//    query3.exec("SELECT BorrowTime from Item where Status = 0;");
//    query4.exec("SELECT ReturnTime from Item where Status = 0;");
    while(1){
        int i = 0;
        //reset the vectors everytime to store new values
        TimeList.clear();
        PawPrintList.clear();
        ItemNameList.clear();
        BorrowTimeList.clear();
        ReturnTimeList.clear();
        MailFlagList.clear();
//        query.prepare("SELECT julianday('now','localtime')*1440 - julianday(BorrowTime)*1440 From Item where Status = 0;");
//        query1.prepare("SELECT PawPrint from Item where Status = 0;");
//        query2.prepare("SELECT ItemName from Item where Status = 0;");
//        query3.prepare("SELECT BorrowTime from Item where Status = 0;");
//        query4.prepare("SELECT ReturnTime from Item where Status = 0;");
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

    }

}
