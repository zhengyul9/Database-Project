#ifndef SENDMAIL_H
#define SENDMAIL_H
#include <QThread>
#include <database.h>

class SendMail : public QThread
{
    Q_OBJECT
public:
    DBManager *data;
    explicit SendMail(QObject *parent = 0);
    void run();
    bool stop;

};

#endif // SENDMAIL_H
