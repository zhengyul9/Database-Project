#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>
#include"database.h"

namespace Ui
{
    class SignUpWindow;
}

class SignUpWindow : public QDialog
{
    Q_OBJECT

public:
    DBManager *data;
    QString Pawprint;
    QString Name;
    int StudentId;
    QString Password;
    explicit SignUpWindow(QWidget *parent = 0);
    ~SignUpWindow();

private slots:
    void on_pushButton_SignUp_clicked();

private:
    Ui::SignUpWindow *ui;
};

#endif // SIGNUPWINDOW_H
