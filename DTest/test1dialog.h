#ifndef TEST1DIALOG_H
#define TEST1DIALOG_H

#include <QDialog>

namespace Ui {
class Test1Dialog;
}

class Test1Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Test1Dialog(QString,QString,int,QWidget *parent = 0);
    ~Test1Dialog();
    void getLegend(QString&,QString&,QString&);
    void getResults(int&,int&,int&);

public slots:
    void accept(void);

private:
    Ui::Test1Dialog *ui;
    QString dt;
    int id_people;
    int res1;
    int res2;
    int res3;
    void loadData(void);
    bool calcRes(QString&);
};

#endif // TEST1DIALOG_H
