#ifndef TEST2DIALOG_H
#define TEST2DIALOG_H

#include <QDialog>

namespace Ui {
class Test2Dialog;
}

class Test2Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Test2Dialog(QString,QString,int,QWidget *parent = 0);
    ~Test2Dialog();
    QString getLegend(void);
    int getResults(void);

public slots:
    void accept(void);

private:
    Ui::Test2Dialog *ui;
    QString dt;
    int id_people;
    int res;
    void loadData(void);
    bool calcRes(QString&);
};

#endif // TEST2DIALOG_H
