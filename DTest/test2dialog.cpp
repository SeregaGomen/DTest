#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "test2dialog.h"
#include "ui_test2dialog.h"

Test2Dialog::Test2Dialog(QString d,QString name,int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test2Dialog)
{
    ui->setupUi(this);
    dt = d;
    id_people = id;
    res = 0;

    setWindowTitle("Опитувальник версії Larocque - " + name);
    loadData();
}

Test2Dialog::~Test2Dialog()
{
    delete ui;
}

void Test2Dialog::loadData(void)
{
    QSqlQuery query;
    QRadioButton* rb[][5] = {
                              {ui->rb1_1,ui->rb1_2,ui->rb1_3,ui->rb1_4,ui->rb1_5},
                              {ui->rb2_1,ui->rb2_2,ui->rb2_3,ui->rb2_4,NULL},
                              {ui->rb3_1,ui->rb3_2,ui->rb3_3,ui->rb3_4,NULL},
                              {ui->rb4_1,ui->rb4_2,ui->rb4_3,ui->rb4_4,NULL},
                              {ui->rb5_1,ui->rb5_2,ui->rb5_3,ui->rb5_4,NULL},
                              {ui->rb6_1,ui->rb6_2,ui->rb6_3,ui->rb6_4,NULL},
                              {ui->rb7_1,ui->rb7_2,ui->rb7_3,ui->rb7_4,NULL},
                              {ui->rb8_1,ui->rb8_2,ui->rb8_3,ui->rb8_4,NULL}
    };
    int q;
    QString s_res;

    query.exec(QString("SELECT * FROM tbl_test2 WHERE f_people = %1 AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        s_res = query.value(3).toString();
        for (int i = 0; i < 8; i++)
        {
            q = s_res.mid(i,1).toInt();
            switch (q)
            {
            case 1:
                rb[i][0]->setChecked(true);
                break;
            case 2:
                rb[i][1]->setChecked(true);
                break;
            case 3:
                rb[i][2]->setChecked(true);
                break;
            case 4:
                rb[i][3]->setChecked(true);
                break;
            case 5:
                rb[i][4]->setChecked(true);
                break;
            }
        }
    }
}

void Test2Dialog::accept(void)
{
    QSqlQuery query;
    QString sql,
            s_res;
    int id = 0;
    bool isFind = false;

    if (!calcRes(s_res))
        return;

    // Сохраняем анекту
    query.exec(QString("SELECT id FROM tbl_test2 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        id = query.value(0).toInt();
        isFind = true;
    }
    if (isFind)
        sql = QString("UPDATE tbl_test2 SET f_res = '%1' WHERE f_people = %2 AND f_dt = '%3'").arg(s_res).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_test2 (f_people,f_dt,f_res) VALUES (%1,'%2','%3')").arg(id_people).arg(dt).arg(s_res);
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    // Определяем номер анкеты
    if (!id)
    {
        query.exec(QString("SELECT id FROM tbl_test2 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
        while (query.next())
            id = query.value(0).toInt();
    }
    QMessageBox::information(this, tr("Результат"),tr("Результат тестування: %1").arg(getLegend()), QMessageBox::Ok);

    // Сохраняем результаты
    isFind = false;
    query.exec(QString("SELECT * FROM tbl_results WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
        isFind = true;
    if (isFind)
        sql = QString("UPDATE tbl_results SET f_id2 = %1,f_res2 = %2,f_legend2 = '%3' WHERE f_people = '%4' AND f_dt = '%5'").arg(id).arg(res).arg(getLegend()).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_results (f_people,f_dt,f_id2,f_res2,f_legend2) VALUES (%1,'%2',%3,%4,'%5')").arg(id_people).arg(dt).arg(id).arg(res).arg(getLegend());
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    QDialog::accept();
}

bool Test2Dialog::calcRes(QString& s_res)
{
    bool isChoised;
    QRadioButton* rb[][5] = {
                              {ui->rb1_1,ui->rb1_2,ui->rb1_3,ui->rb1_4,ui->rb1_5},
                              {ui->rb2_1,ui->rb2_2,ui->rb2_3,ui->rb2_4,NULL},
                              {ui->rb3_1,ui->rb3_2,ui->rb3_3,ui->rb3_4,NULL},
                              {ui->rb4_1,ui->rb4_2,ui->rb4_3,ui->rb4_4,NULL},
                              {ui->rb5_1,ui->rb5_2,ui->rb5_3,ui->rb5_4,NULL},
                              {ui->rb6_1,ui->rb6_2,ui->rb6_3,ui->rb6_4,NULL},
                              {ui->rb7_1,ui->rb7_2,ui->rb7_3,ui->rb7_4,NULL},
                              {ui->rb8_1,ui->rb8_2,ui->rb8_3,ui->rb8_4,NULL}
    };

    s_res = "";
    // Проверка на наличие ответов на все вопросы анкеты
    for (int i = 0; i < 8; i++)
    {
        isChoised = false;
        if (rb[i][0]->isChecked())
        {
            s_res += "1";
            isChoised = true;
        }
        else if (rb[i][1]->isChecked())
        {
            s_res += "2";
            isChoised = true;
        }
        else if (rb[i][2]->isChecked())
        {
            s_res += "3";
            isChoised = true;
        }
        else if (rb[i][3]->isChecked())
        {
            s_res += "4";
            isChoised = true;
        }
        else if (i == 0 && rb[i][4]->isChecked())
        {
            s_res += "5";
            isChoised = true;
        }
        if (!isChoised)
        {
            QMessageBox::information(this, tr("Помилка"), tr("Не задана відповіднь на питання: %1!").arg(i + 1));
            return false;
        }

        if ((i == 0 || i == 1 || i == 2 || i == 3 || i == 6 || i == 7))
        {
            if (rb[i][0]->isChecked())
                res += 4;
            else if (rb[i][1]->isChecked())
                res += 3;
            else if (rb[i][2]->isChecked())
                res += 2;
            else if (rb[i][3]->isChecked())
                res += 1;
        }
        else
        {
            if (rb[i][0]->isChecked())
                res += 1;
            else if (rb[i][1]->isChecked())
                res += 2;
            else if (rb[i][2]->isChecked())
                res += 3;
            else if (rb[i][3]->isChecked())
                res += 4;
        }
    }
    return true;
}

QString Test2Dialog::getLegend(void)
{
    QString legend;

    if (res < 16)
        legend = "Низкий уровень ";
    else if (res <= 16 && res <= 23)
        legend = "Средний уровень";
    else
        legend = "Высокий уровень";
    return legend;
}

int Test2Dialog::getResults(void)
{
    return res;
}


