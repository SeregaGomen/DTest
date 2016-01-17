#ifndef TEST6DIALOG_H
#define TEST6DIALOG_H

#include <QDialog>

namespace Ui {
class Test6Dialog;
}

class Test6Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Test6Dialog(QString,QString,int,QWidget *parent = 0);
    ~Test6Dialog();
    QString getLegend(void);
    int getResults(void);

public slots:
    void accept(void);

private:
    Ui::Test6Dialog *ui;
    QString dt;
    int id_people;
    int res;
    void loadData(void);
    bool calcRes(QString&);
};

#endif // TEST6DIALOG_H
