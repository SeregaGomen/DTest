#ifndef GETSTUDENTDIALOG_H
#define GETSTUDENTDIALOG_H

#include <QDialog>

namespace Ui {
class GetStudentDialog;
}

class GetStudentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetStudentDialog(QWidget *parent = 0);
    ~GetStudentDialog();
    QString getName(void);
    QString getSex(void);
    QString getDate(void);
    int getAge(void);
    int getHeight(void);
    int getWeight(void);
    void initDialog(void);
    void initDialog(QString,QString,int,int,int,QString);

private slots:
    void slotChangeText(const QString&);

private:
    Ui::GetStudentDialog *ui;
};

#endif // GETSTUDENTDIALOG_H
