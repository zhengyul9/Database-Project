#ifndef ADDITEMWINDOW_H
#define ADDITEMWINDOW_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AddItemWindow;
}

class AddItemWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddItemWindow(QWidget *parent = 0);
    ~AddItemWindow();
    DBManager *data;
    int ItemId;
    QString ItemName;
    QString Location;
    int Status;
    int BorrowLength;
    //2 times...

private slots:
    void on_pushButton_Add_clicked();

private:
    Ui::AddItemWindow *ui;
};

#endif // ADDITEMWINDOW_H
