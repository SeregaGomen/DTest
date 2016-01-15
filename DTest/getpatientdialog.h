#ifndef GETPATIENTDIALOG_H
#define GETPATIENTDIALOG_H


#include <QDialog>
#include <QItemSelection>

namespace Ui {
class GetPatientDialog;
}

class GetPatientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetPatientDialog(QWidget *parent = 0);
    ~GetPatientDialog();
    QString getName(void);
    QString getSex(void);
    QString getDate(void);
    int getAge(void);
    int getHeight(void);
    int getWeight(void);
    int getID(void);
    void initDialog(void);

private slots:
    void slotEnabledBtn(QItemSelection, QItemSelection);

private:
    Ui::GetPatientDialog *ui;
};

#endif // GETPATIENTDIALOG_H
