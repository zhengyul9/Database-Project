#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "signupwindow.h"
#include "mainwindow.h"
#include "adminview.h"
#include "sendmail.h"
#include <QProcess>

LoginWindow::LoginWindow(QWidget *parent) : QDialog(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->lineEdit_Password->setEchoMode(QLineEdit::Password);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_Signup_clicked()
{
    SignUpWindow s;
    s.data = data;
    s.setModal(true);
    s.exec();
}

void LoginWindow::on_pushButton_Login_clicked()
{
    Password = ui->lineEdit_Password->text();
    Pawprint = ui->lineEdit_Pawprint->text();

    if(data->check(Pawprint,Password) == 1)
    {
        hide();
        cout << "Password is mathched." << endl;
        if(data->getUserType(Pawprint) == 1){

            MainWindow *m = new MainWindow();
            m->data = data;
            m->Pawprint = Pawprint;
            m->setAttribute(Qt::WA_DeleteOnClose);
            m->show();

        }
        else{
            //start other program
            QProcess *process = new QProcess(this);

            process->start("//Users//Ben//Dropbox//cs3380//build-SendMailBackEnd-Desktop_Qt_5_10_0_clang_64bit-Debug//SendMailBackEnd");
//            SendMail SM;
//            SM.data = data;
//            SM.start();
            AdminView av;
            av.data = data;
            av.setModal(true);
            av.exec();

        }


    }
    else
    {
        ui->label_error1->setStyleSheet("color:red");
        ui->label_error1->setText("Pawprint or Password is invalid");
        cout<<"Password is invalid."<<endl;
    }
}
