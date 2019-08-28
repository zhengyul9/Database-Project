#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Load_clicked()
{
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQueryModel * modal1 = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT ItemId, ItemName, Location from Item Where Status = 1");
    query.exec();
    modal->setQuery(query);
    ui->AvaliableItem->setModel(modal);
    QSqlQuery query1;
    query1.prepare("SELECT ItemId, ItemName, Location from Item Where Status = 0 and Pawprint = :Pawprint");
    query1.bindValue(":Pawprint",Pawprint);
    query1.exec();
    modal1->setQuery(query1);
    ui->BorrowedItem->setModel(modal1);


}

void MainWindow::on_pushButton_CheckOut_clicked()
{
    //Need to add error handling
    QString id = ui->lineEdit_ItemId->text();
    int ItemId = id.toInt();
   // <<"correct ID is" << ItemId;
    QSqlQuery query;
    query.prepare("UPDATE Item set Status = 0, Pawprint = :Pawprint, BorrowTime = datetime('now', 'localtime'), ReturnTime = datetime('now','localtime','+' || BorrowLength || ' minutes') where ItemId = :ItemId");
    query.bindValue(":ItemId",ItemId);
    query.bindValue(":Pawprint",Pawprint);
    query.exec();
}

void MainWindow::on_pushButton_Return_clicked()
{

    //----------------------------------------------------------------------
    String id;
    VideoCapture cap(0); // open the video camera no. 0

     cap.set(CV_CAP_PROP_FRAME_WIDTH,320);
     cap.set(CV_CAP_PROP_FRAME_HEIGHT,240);

    if (!cap.isOpened())  // if not success, exit program
    {
        cout << "Cannot open the video cam" << endl;
       // return -1;

    }

    //example code from Open CV
    ImageScanner scanner;
    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

    cout << "Frame size : " << dWidth << " x " << dHeight << endl;

    namedWindow("ScanWindow",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    int flag = 0;
    do{
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        Mat grey;
        cvtColor(frame,grey,CV_BGR2GRAY);

        int width = frame.cols;
        int height = frame.rows;
        uchar *raw = (uchar *)grey.data;
        // wrap image data
        // example from ZBAR
        Image image(width, height, "Y800", raw, width * height);
        // scan the image for barcodes
        int n = scanner.scan(image);
        // extract results
        for(Image::SymbolIterator symbol = image.symbol_begin();
            symbol != image.symbol_end();
            ++symbol) {
            vector<Point> vp;
            // do something useful with results
            id = symbol->get_data();
            cout << "decoded " << symbol->get_type_name()  << " symbol \"" << symbol->get_data() << '"' <<" "<< endl;
            flag = 1;
            int n = symbol->get_location_size();
            for(int i=0;i<n;i++){
                vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
            }
            RotatedRect r = minAreaRect(vp);
            Point2f pts[4];
            r.points(pts);
            for(int i=0;i<4;i++){
                line(frame,pts[i],pts[(i+1)%4],Scalar(255,0,0),3);
            }
            //cout<<"Angle: "<<r.angle<<endl;
        }

        imshow("ScanWindow", frame); //show the frame in "MyVideo" window

        if (waitKey(1) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key is pressed by user" << endl;
            break;
        }
    }while(flag == 0);
    //----------------------------------------------------------------------

    //Need to add error handling
    int ItemId = stoi(id);
   // <<"correct ID is" << ItemId;
    //returning item
    QSqlQuery query;
    query.prepare("UPDATE Item set Status = 1, Pawprint = NULL where ItemId = :ItemId");
    query.bindValue(":ItemId",ItemId);
    query.exec();
    cvDestroyWindow("ScanWindow");


    //load again
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQueryModel * modal1 = new QSqlQueryModel();
    QSqlQuery query1;
    query1.prepare("SELECT ItemId, ItemName, Location from Item Where Status = 1");
    query1.exec();
    modal->setQuery(query1);
    ui->AvaliableItem->setModel(modal);
    QSqlQuery query2;
    query2.prepare("SELECT ItemId, ItemName, Location from Item Where Status = 0 and Pawprint = :Pawprint");
    query2.bindValue(":Pawprint",Pawprint);
    query2.exec();
    modal1->setQuery(query2);
    ui->BorrowedItem->setModel(modal1);

}
