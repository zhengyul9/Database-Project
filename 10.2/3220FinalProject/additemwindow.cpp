#include "additemwindow.h"
#include "ui_additemwindow.h"

AddItemWindow::AddItemWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddItemWindow)
{
    ui->setupUi(this);
}

AddItemWindow::~AddItemWindow()
{
    delete ui;
}

void AddItemWindow::on_pushButton_Add_clicked()
{
    QString ItemId1 = ui->lineEdit_ItemId->text();
    ItemId = ItemId1.toInt();
    ItemName = ui->lineEdit_Name->text();
    Location = ui->lineEdit_Location->text();
    QString BorrowLength1 = ui->lineEdit_BorrowLength->text();
    BorrowLength = BorrowLength1.toInt();
    data->InsertItem(ItemId, ItemName, Location, BorrowLength);
    hide();
}
