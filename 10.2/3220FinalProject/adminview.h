#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include <QDialog>
#include "database.h"

namespace Ui {
class AdminView;
}

class AdminView : public QDialog
{
    Q_OBJECT

public:
    explicit AdminView(QWidget *parent = 0);
    DBManager *data;
    ~AdminView();

private slots:
    void on_pushButton_LoadTable_clicked();

    void on_pushButton_Delete_clicked();

    void on_pushButton_AddItem_clicked();

private:
    Ui::AdminView *ui;
};

#endif // ADMINVIEW_H
