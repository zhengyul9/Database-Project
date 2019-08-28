#include "signupwindow.h"
#include "ui_signupwindow.h"
SignUpWindow::SignUpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_Password1->setEchoMode(QLineEdit::Password);
}

SignUpWindow::~SignUpWindow()
{
    delete ui;
}

void SignUpWindow::on_pushButton_SignUp_clicked()
{

    Pawprint = ui->lineEdit_Pawprint->text();
      Name = ui->lineEdit_Name->text();

      Password = ui->lineEdit_Password->text();
      QString passowrd1 = ui->lineEdit_Password1->text();
      QString ID = ui->lineEdit_StudentID->text();
      StudentId = ID.toInt();

      if(Password == passowrd1 && data->check(StudentId) == 1){
          data->CreateUser(Pawprint,Name,StudentId,1,Password);
          hide();

          ui->label_error->setText("Password not match");
      }
      else{
          if(data->check(StudentId) != 1)
          {
              ui->label_error->setStyleSheet("color:red");
              ui->label_error->setText("Id not found");
              cout <<"create user fail!"<<endl;
          }
          else if(Password != passowrd1){
              ui->label_error->setStyleSheet("color:red");
              ui->label_error->setText("Password Not match!");
              cout <<"create user fail!"<<endl;
          }
      }


}
