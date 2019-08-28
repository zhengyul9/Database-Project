#include "adminview.h"
#include "ui_adminview.h"
#include "additemwindow.h"

AdminView::AdminView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminView)
{
    ui->setupUi(this);
}

AdminView::~AdminView()
{
    delete ui;
}

void AdminView::on_pushButton_LoadTable_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ItemId, ItemName, Location from Item Where Status = 1");
    query.exec();
    modal->setQuery(query);
    ui->ItemTable->setModel(modal);

    QSqlQueryModel * modal1 = new QSqlQueryModel();
    QSqlQuery query1;
    query1.prepare("SELECT ItemId, ItemName, Item.Pawprint, BorrowTime, ReturnTime from Item, User where Status = 0 and Item.Pawprint = User.Pawprint");
    query1.exec();
    modal1->setQuery(query1);
    ui->BorrowedItem->setModel(modal1);
}

void AdminView::on_pushButton_Delete_clicked()
{
    //Need to add error handling
    QString id = ui->lineEdit_DeleteId->text();
    int ItemId = id.toInt();
    cout<<"correct ID is" << ItemId;
    QSqlQuery query;
    query.prepare("DELETE from Item Where ItemID = :ItemId");
    query.bindValue(":ItemId",ItemId);
    query.exec();
}

void AdminView::on_pushButton_AddItem_clicked()
{

    AddItemWindow aiw;
    aiw.data = data;
    aiw.setModal(true);
    aiw.exec();
}
