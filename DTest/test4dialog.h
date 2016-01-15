#ifndef TEST4DIALOG_H
#define TEST4DIALOG_H

#include <QDialog>

namespace Ui {
class Test4Dialog;
}

class Test4Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Test4Dialog(QString,QString,QString,int,int,int,int,QWidget *parent = 0);
    ~Test4Dialog();
    QString getLegend(void);
    int getResults(void);

public slots:
    void accept(void);

private:
    Ui::Test4Dialog *ui;
    QString name;
    QString sex;
    QString dt;
    int age;
    int height;
    int weight;
    int id_people;
    int res;
    void loadData(void);
    bool calcRes(QString&,QString&);
};

#endif // TEST4DIALOG_H
