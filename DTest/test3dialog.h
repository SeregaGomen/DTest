#ifndef TEST3DIALOG_H
#define TEST3DIALOG_H

#include <QDialog>

namespace Ui {
class Test3Dialog;
}

class Test3Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Test3Dialog(QString,QString,QString,int,int,int,int,QWidget *parent = 0);
    ~Test3Dialog();
    QString getLegend(void);
    int getResults(void);

public slots:
    void accept(void);

private:
    Ui::Test3Dialog *ui;
    QString name;
    QString sex;
    QString dt;
    int age;
    int height;
    int weight;
    int id_people;
    int res;
    void loadData(void);
    bool calcRes(QString&);
};

#endif // TEST3DIALOG_H
