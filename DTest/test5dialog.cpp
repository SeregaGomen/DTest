#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "test5dialog.h"
#include "ui_test5dialog.h"

Test5Dialog::Test5Dialog(QString d,QString n,int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test5Dialog)
{
    ui->setupUi(this);
    ui->groupBox_41->hide();

    dt = d;
    id_people = id;
    res = 0;

    setWindowTitle("Методика оценки биологического возраста В.П. Войтенко - " + n);
    loadData();
}

Test5Dialog::~Test5Dialog()
{
    delete ui;
}

void Test5Dialog::loadData(void)
{
    QSqlQuery query;
    QRadioButton *rb[][4] = {
                              {ui->rb1_1,ui->rb1_2,NULL,NULL},
                              {ui->rb2_1,ui->rb2_2,NULL,NULL},
                              {ui->rb3_1,ui->rb3_2,NULL,NULL},
                              {ui->rb4_1,ui->rb4_2,NULL,NULL},
                              {ui->rb5_1,ui->rb5_2,NULL,NULL},
                              {ui->rb6_1,ui->rb6_2,NULL,NULL},
                              {ui->rb7_1,ui->rb7_2,NULL,NULL},
                              {ui->rb8_1,ui->rb8_2,NULL,NULL},
                              {ui->rb9_1,ui->rb9_2,NULL,NULL},
                              {ui->rb10_1,ui->rb10_2,NULL,NULL},
                              {ui->rb11_1,ui->rb11_2,NULL,NULL},
                              {ui->rb12_1,ui->rb12_2,NULL,NULL},
                              {ui->rb13_1,ui->rb13_2,NULL,NULL},
                              {ui->rb14_1,ui->rb14_2,NULL,NULL},
                              {ui->rb15_1,ui->rb15_2,NULL,NULL},
                              {ui->rb16_1,ui->rb16_2,NULL,NULL},
                              {ui->rb17_1,ui->rb17_2,NULL,NULL},
                              {ui->rb18_1,ui->rb18_2,NULL,NULL},
                              {ui->rb19_1,ui->rb19_2,NULL,NULL},
                              {ui->rb20_1,ui->rb20_2,NULL,NULL},
                              {ui->rb21_1,ui->rb21_2,NULL,NULL},
                              {ui->rb22_1,ui->rb22_2,NULL,NULL},
                              {ui->rb23_1,ui->rb23_2,NULL,NULL},
                              {ui->rb24_1,ui->rb24_2,NULL,NULL},
                              {ui->rb25_1,ui->rb25_2,NULL,NULL},
                              {ui->rb26_1,ui->rb26_2,NULL,NULL},
                              {ui->rb27_1,ui->rb27_2,NULL,NULL},
                              {ui->rb28_1,ui->rb28_2,NULL,NULL},
                              {ui->rb29_1,ui->rb29_2,ui->rb29_3,ui->rb29_4}
    };
    int q;
    QString res;

    query.exec(QString("SELECT * FROM tbl_test5 WHERE f_people = %1 AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        res = query.value(3).toString();
        for (int i = 0; i < 29; i++)
        {
            q = res.mid(i,1).toInt();
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
            }
        }
    }
}

void Test5Dialog::accept(void)
{
    QSqlQuery query;
    QString sql,
            s_res;
    int id = 0;
    bool isFind = false;

    if (!calcRes(s_res))
        return;

    // Сохраняем анекту
    query.exec(QString("SELECT id FROM tbl_test5 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        id = query.value(0).toInt();
        isFind = true;
    }
    if (isFind)
        sql = QString("UPDATE tbl_test5 SET f_res = '%1' WHERE f_people = %2 AND f_dt = '%3'").arg(s_res).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_test5 (f_people,f_dt,f_res) VALUES (%1,'%2','%3')").arg(id_people).arg(dt).arg(s_res);
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    // Определяем номер анкеты
    if (!id)
    {
        query.exec(QString("SELECT id FROM tbl_test5 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
        while (query.next())
            id = query.value(0).toInt();
    }
    QMessageBox::information(this, tr("Результат"),tr("Результат тестування: %2 - %1").arg(getLegend()).arg(res), QMessageBox::Ok);

    // Сохраняем результаты
    isFind = false;
    query.exec(QString("SELECT * FROM tbl_results WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
        isFind = true;
    if (isFind)
        sql = QString("UPDATE tbl_results SET f_id5 = %1,f_res5 = %2,f_legend5 = '%3' WHERE f_people = '%4' AND f_dt = '%5'").arg(id).arg(res).arg(getLegend()).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_results (f_people,f_dt,f_id5,f_res5,f_legend5) VALUES (%1,'%2',%3,%4,'%5')").arg(id_people).arg(dt).arg(id).arg(res).arg(getLegend());
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    QDialog::accept();
}

bool Test5Dialog::calcRes(QString& s_res)
{
    QString sex;
    bool isChoised;
    QSqlQuery query;
    QRadioButton *rb[][4] = {
                              {ui->rb1_1,ui->rb1_2,NULL,NULL},
                              {ui->rb2_1,ui->rb2_2,NULL,NULL},
                              {ui->rb3_1,ui->rb3_2,NULL,NULL},
                              {ui->rb4_1,ui->rb4_2,NULL,NULL},
                              {ui->rb5_1,ui->rb5_2,NULL,NULL},
                              {ui->rb6_1,ui->rb6_2,NULL,NULL},
                              {ui->rb7_1,ui->rb7_2,NULL,NULL},
                              {ui->rb8_1,ui->rb8_2,NULL,NULL},
                              {ui->rb9_1,ui->rb9_2,NULL,NULL},
                              {ui->rb10_1,ui->rb10_2,NULL,NULL},
                              {ui->rb11_1,ui->rb11_2,NULL,NULL},
                              {ui->rb12_1,ui->rb12_2,NULL,NULL},
                              {ui->rb13_1,ui->rb13_2,NULL,NULL},
                              {ui->rb14_1,ui->rb14_2,NULL,NULL},
                              {ui->rb15_1,ui->rb15_2,NULL,NULL},
                              {ui->rb16_1,ui->rb16_2,NULL,NULL},
                              {ui->rb17_1,ui->rb17_2,NULL,NULL},
                              {ui->rb18_1,ui->rb18_2,NULL,NULL},
                              {ui->rb19_1,ui->rb19_2,NULL,NULL},
                              {ui->rb20_1,ui->rb20_2,NULL,NULL},
                              {ui->rb21_1,ui->rb21_2,NULL,NULL},
                              {ui->rb22_1,ui->rb22_2,NULL,NULL},
                              {ui->rb23_1,ui->rb23_2,NULL,NULL},
                              {ui->rb24_1,ui->rb24_2,NULL,NULL},
                              {ui->rb25_1,ui->rb25_2,NULL,NULL},
                              {ui->rb26_1,ui->rb26_2,NULL,NULL},
                              {ui->rb27_1,ui->rb27_2,NULL,NULL},
                              {ui->rb28_1,ui->rb28_2,NULL,NULL},
                              {ui->rb29_1,ui->rb29_2,ui->rb29_3,ui->rb29_4}
    };

    query.exec(QString("SELECT * FROM tbl_people WHERE id = '%1'").arg(id_people));
    while (query.next())
        sex = query.value(2).toString().toUpper();


    s_res = "";
    // Проверка на наличие ответов на все вопросы анкеты
    for (int i = 0; i < 29; i++)
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
        else if (rb[i][2] && rb[i][2]->isChecked())
        {
            s_res += "3";
            isChoised = true;
        }
        else if (rb[i][3] && rb[i][3]->isChecked())
        {
            s_res += "4";
            isChoised = true;
        }
        if (!isChoised)
        {
            QMessageBox::information(this, tr("Помилка"), tr("Не задана відповіднь на питання: %1!").arg(i + 1));
            return false;
        }
        if (((i >= 0 && i < 8) || (i >= 9 && i < 11) || (i >= 13 && i <= 17) || (i >= 19 && i <= 27)) && rb[i][0]->isChecked())
            res++;
        if (!((i >= 0 && i < 8) || (i >= 9 && i < 11) || (i >= 13 && i <= 17) || (i >= 19 && i <= 27)) && rb[i][1]->isChecked())
            res++;
        if (i == 28)
        {
            if (rb[i][2]->isChecked())
                res++;
            if (rb[i][3]->isChecked())
                res++;
        }
    }
    if (sex == "МУЖ.")
        res = 0.629*float(res) + 18.56;
    else
        res = 0.581*float(res) + 17.24;
    return true;
}

QString Test5Dialog::getLegend(void)
{
    QString legend;

    legend = QString("биологический возраст");
    return legend;
}

int Test5Dialog::getResults(void)
{
    return res;
}


