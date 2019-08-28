#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <zbar.h>
#include <iostream>

using namespace cv;
using namespace std;
using namespace zbar;

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    DBManager *data;
    QString Pawprint;
    ~MainWindow();

private slots:
    void on_pushButton_Load_clicked();

    void on_pushButton_CheckOut_clicked();

    void on_pushButton_Return_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
