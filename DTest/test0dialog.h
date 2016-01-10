#ifndef TEST0DIALOG_H
#define TEST0DIALOG_H

#include <QDialog>

namespace Ui {
class Test0Dialog;
}

class Test0Dialog : public QDialog
{
    Q_OBJECT

public slots:
    void accept(void);

public:
    explicit Test0Dialog(QWidget *parent = 0);
    ~Test0Dialog();
    void initDialog(void);

private slots:
    void slotChangeText(const QString&);

private:
    Ui::Test0Dialog *ui;
};

#endif // TEST0DIALOG_H
