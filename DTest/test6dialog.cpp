#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "test6dialog.h"
#include "ui_test6dialog.h"

Test6Dialog::Test6Dialog(QString d,QString n, int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test6Dialog)
{
    ui->setupUi(this);
    dt = d;
    id_people = id;
    res = 0;

    loadData();
    setWindowTitle("Краткий опросник ВОЗ для оценки качества жизни - " + n);
}

Test6Dialog::~Test6Dialog()
{
    delete ui;
}

void Test6Dialog::loadData(void)
{
    QSqlQuery query;
    QRadioButton* rb[][5] = {
                              {ui->rb1_1,ui->rb1_2,ui->rb1_3,ui->rb1_4,ui->rb1_5},
                              {ui->rb2_1,ui->rb2_2,ui->rb2_3,ui->rb2_4,ui->rb2_5},
                              {ui->rb3_1,ui->rb3_2,ui->rb3_3,ui->rb3_4,ui->rb3_5},
                              {ui->rb4_1,ui->rb4_2,ui->rb4_3,ui->rb4_4,ui->rb4_5},
                              {ui->rb5_1,ui->rb5_2,ui->rb5_3,ui->rb5_4,ui->rb5_5},
                              {ui->rb6_1,ui->rb6_2,ui->rb6_3,ui->rb6_4,ui->rb6_5},
                              {ui->rb7_1,ui->rb7_2,ui->rb7_3,ui->rb7_4,ui->rb7_5},
                              {ui->rb8_1,ui->rb8_2,ui->rb8_3,ui->rb8_4,ui->rb8_5},
                              {ui->rb9_1,ui->rb9_2,ui->rb9_3,ui->rb9_4,ui->rb9_5},
                              {ui->rb10_1,ui->rb10_2,ui->rb10_3,ui->rb10_4,ui->rb10_5},
                              {ui->rb11_1,ui->rb11_2,ui->rb11_3,ui->rb11_4,ui->rb11_5},
                              {ui->rb12_1,ui->rb12_2,ui->rb12_3,ui->rb12_4,ui->rb12_5},
                              {ui->rb13_1,ui->rb13_2,ui->rb13_3,ui->rb13_4,ui->rb13_5},
                              {ui->rb14_1,ui->rb14_2,ui->rb14_3,ui->rb14_4,ui->rb14_5},
                              {ui->rb15_1,ui->rb15_2,ui->rb15_3,ui->rb15_4,ui->rb15_5},
                              {ui->rb16_1,ui->rb16_2,ui->rb16_3,ui->rb16_4,ui->rb16_5},
                              {ui->rb17_1,ui->rb17_2,ui->rb17_3,ui->rb17_4,ui->rb17_5},
                              {ui->rb18_1,ui->rb18_2,ui->rb18_3,ui->rb18_4,ui->rb18_5},
                              {ui->rb19_1,ui->rb19_2,ui->rb19_3,ui->rb19_4,ui->rb19_5},
                              {ui->rb20_1,ui->rb20_2,ui->rb20_3,ui->rb20_4,ui->rb20_5},
                              {ui->rb21_1,ui->rb21_2,ui->rb21_3,ui->rb21_4,ui->rb21_5},
                              {ui->rb22_1,ui->rb22_2,ui->rb22_3,ui->rb22_4,ui->rb22_5},
                              {ui->rb23_1,ui->rb23_2,ui->rb23_3,ui->rb23_4,ui->rb23_5},
                              {ui->rb24_1,ui->rb24_2,ui->rb24_3,ui->rb24_4,ui->rb24_5},
                              {ui->rb25_1,ui->rb25_2,ui->rb25_3,ui->rb25_4,ui->rb25_5},
                              {ui->rb26_1,ui->rb26_2,ui->rb26_3,ui->rb26_4,ui->rb26_5}
    };
    int q;
    QString res;

    // Если такая анкета уже есть, то загружаем ее
    query.exec(QString("SELECT * FROM tbl_test6 WHERE f_people = %1 AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        res = query.value(3).toString();
        for (int i = 0; i < 26; i++)
        {
            q = res.mid(i,1).toInt();
            if (q >= 1 || q <= 5)
                rb[i][q - 1]->setChecked(true);
        }
    }
}

void Test6Dialog::accept(void)
{
    QSqlQuery query;
    QString legend,
            sql,
            s_res;
    int id = 0;
    bool isFind = false;

    if (!calcRes(s_res))
        return;

    // Сохраняем анекту
    query.exec(QString("SELECT id FROM tbl_test6 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        id = query.value(0).toInt();
        isFind = true;
    }
    if (isFind)
        sql = QString("UPDATE tbl_test6 SET f_res = '%1' WHERE f_people = %2 AND f_dt = '%3'").arg(s_res).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_test6 (f_people,f_dt,f_res) VALUES (%1,'%2','%3')").arg(id_people).arg(dt).arg(s_res);
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    // Определяем номер анкеты
    if (!id)
    {
        query.exec(QString("SELECT id FROM tbl_test6 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
        while (query.next())
            id = query.value(0).toInt();
    }
    legend = getLegend();
    QMessageBox::information(this, tr("Результат"),tr("Результат тестування: %2 - %1").arg(legend).arg(res), QMessageBox::Ok);

    // Сохраняем результаты
    isFind = false;
    query.exec(QString("SELECT * FROM tbl_results WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
        isFind = true;
    if (isFind)
        sql = QString("UPDATE tbl_results SET f_id6 = %1,f_res6 = %2,f_legend6 = '%3' WHERE f_people = '%4' AND f_dt = '%5'").arg(id).arg(res).arg(legend).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_results (f_people,f_dt,f_id6,f_res6,f_legend6) VALUES (%1,'%2',%3,%4,'%5')").arg(id_people).arg(dt).arg(id).arg(res).arg(getLegend());
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    QDialog::accept();
}

bool Test6Dialog::calcRes(QString& s_res)
{
    bool isChoised;
    QRadioButton* rb[][5] = {
                              {ui->rb1_1,ui->rb1_2,ui->rb1_3,ui->rb1_4,ui->rb1_5},
                              {ui->rb2_1,ui->rb2_2,ui->rb2_3,ui->rb2_4,ui->rb2_5},
                              {ui->rb3_1,ui->rb3_2,ui->rb3_3,ui->rb3_4,ui->rb3_5},
                              {ui->rb4_1,ui->rb4_2,ui->rb4_3,ui->rb4_4,ui->rb4_5},
                              {ui->rb5_1,ui->rb5_2,ui->rb5_3,ui->rb5_4,ui->rb5_5},
                              {ui->rb6_1,ui->rb6_2,ui->rb6_3,ui->rb6_4,ui->rb6_5},
                              {ui->rb7_1,ui->rb7_2,ui->rb7_3,ui->rb7_4,ui->rb7_5},
                              {ui->rb8_1,ui->rb8_2,ui->rb8_3,ui->rb8_4,ui->rb8_5},
                              {ui->rb9_1,ui->rb9_2,ui->rb9_3,ui->rb9_4,ui->rb9_5},
                              {ui->rb10_1,ui->rb10_2,ui->rb10_3,ui->rb10_4,ui->rb10_5},
                              {ui->rb11_1,ui->rb11_2,ui->rb11_3,ui->rb11_4,ui->rb11_5},
                              {ui->rb12_1,ui->rb12_2,ui->rb12_3,ui->rb12_4,ui->rb12_5},
                              {ui->rb13_1,ui->rb13_2,ui->rb13_3,ui->rb13_4,ui->rb13_5},
                              {ui->rb14_1,ui->rb14_2,ui->rb14_3,ui->rb14_4,ui->rb14_5},
                              {ui->rb15_1,ui->rb15_2,ui->rb15_3,ui->rb15_4,ui->rb15_5},
                              {ui->rb16_1,ui->rb16_2,ui->rb16_3,ui->rb16_4,ui->rb16_5},
                              {ui->rb17_1,ui->rb17_2,ui->rb17_3,ui->rb17_4,ui->rb17_5},
                              {ui->rb18_1,ui->rb18_2,ui->rb18_3,ui->rb18_4,ui->rb18_5},
                              {ui->rb19_1,ui->rb19_2,ui->rb19_3,ui->rb19_4,ui->rb19_5},
                              {ui->rb20_1,ui->rb20_2,ui->rb20_3,ui->rb20_4,ui->rb20_5},
                              {ui->rb21_1,ui->rb21_2,ui->rb21_3,ui->rb21_4,ui->rb21_5},
                              {ui->rb22_1,ui->rb22_2,ui->rb22_3,ui->rb22_4,ui->rb22_5},
                              {ui->rb23_1,ui->rb23_2,ui->rb23_3,ui->rb23_4,ui->rb23_5},
                              {ui->rb24_1,ui->rb24_2,ui->rb24_3,ui->rb24_4,ui->rb24_5},
                              {ui->rb25_1,ui->rb25_2,ui->rb25_3,ui->rb25_4,ui->rb25_5},
                              {ui->rb26_1,ui->rb26_2,ui->rb26_3,ui->rb26_4,ui->rb26_5}
    };

    s_res = "";
    res = 0;
    // Проверка на наличие ответов на все вопросы анкеты
    for (int i = 0; i < 26; i++)
    {
        isChoised = false;
        if (rb[i][0]->isChecked())
        {
            s_res += "1";
            isChoised = true;
            if (i != 2 && i != 3)
                res += 1;
            else
                res += 5;
        }
        else if (rb[i][1]->isChecked())
        {
            s_res += "2";
            isChoised = true;
            if (i != 2 && i != 3)
                res += 2;
            else
                res += 4;
        }
        else if (rb[i][2]->isChecked())
        {
            s_res += "3";
            isChoised = true;
            res += 3;
        }
        else if (rb[i][3]->isChecked())
        {
            s_res += "4";
            isChoised = true;
            if (i != 2 && i != 3)
                res += 4;
            else
                res += 2;
        }
        else if (rb[i][4]->isChecked())
        {
            s_res += "5";
            isChoised = true;
            if (i != 2 && i != 3)
                res += 5;
            else
                res += 1;
        }
        if (!isChoised)
        {
            QMessageBox::information(this, tr("Помилка"), tr("Не задана відповіднь на питання: %1!").arg(i + 1));
            return false;
        }
    }
    return true;
}

QString Test6Dialog::getLegend(void)
{
    if (res <= 71)
        return QString("низкий уровень удовлетворенности качеством жизни");
    else if (res > 71 && res <= 89)
        return QString("средний уровень удовлетворенности качеством жизни");
    return QString("высокий уровень удовлетворенности качеством жизни");
}

int Test6Dialog::getResults(void)
{
    return res;
}


