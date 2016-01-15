#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "test1dialog.h"
#include "ui_test1dialog.h"

Test1Dialog::Test1Dialog(QString d,QString n,QString s,int a,int h, int w,int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test1Dialog)
{
    ui->setupUi(this);
    name = n;
    sex = s;
    age = a;
    height = h;
    weight = w;
    dt = d;
    id_people = id;
    res1 = res2 = res3 = 0;

    setWindowTitle("Особистісний опитувальник Айзенка - " + name);
    loadData();
}

Test1Dialog::~Test1Dialog()
{
    delete ui;
}

void Test1Dialog::loadData(void)
{
    QSqlQuery query(QString("SELECT id FROM tbl_people WHERE f_name = '%1' AND f_sex = '%2' AND f_age = %3").arg(name.toUpper()).arg(sex.toUpper()).arg(age));
    QRadioButton* rb[][2] = {
                              {ui->rb1_1,ui->rb1_2},
                              {ui->rb2_1,ui->rb2_2},
                              {ui->rb3_1,ui->rb3_2},
                              {ui->rb4_1,ui->rb4_2},
                              {ui->rb5_1,ui->rb5_2},
                              {ui->rb6_1,ui->rb6_2},
                              {ui->rb7_1,ui->rb7_2},
                              {ui->rb8_1,ui->rb8_2},
                              {ui->rb9_1,ui->rb9_2},
                              {ui->rb10_1,ui->rb10_2},
                              {ui->rb11_1,ui->rb11_2},
                              {ui->rb12_1,ui->rb12_2},
                              {ui->rb13_1,ui->rb13_2},
                              {ui->rb14_1,ui->rb14_2},
                              {ui->rb15_1,ui->rb15_2},
                              {ui->rb16_1,ui->rb16_2},
                              {ui->rb17_1,ui->rb17_2},
                              {ui->rb18_1,ui->rb18_2},
                              {ui->rb19_1,ui->rb19_2},
                              {ui->rb20_1,ui->rb20_2},
                              {ui->rb21_1,ui->rb21_2},
                              {ui->rb22_1,ui->rb22_2},
                              {ui->rb23_1,ui->rb23_2},
                              {ui->rb24_1,ui->rb24_2},
                              {ui->rb25_1,ui->rb25_2},
                              {ui->rb26_1,ui->rb26_2},
                              {ui->rb27_1,ui->rb27_2},
                              {ui->rb28_1,ui->rb28_2},
                              {ui->rb29_1,ui->rb29_2},
                              {ui->rb30_1,ui->rb30_2},
                              {ui->rb31_1,ui->rb31_2},
                              {ui->rb32_1,ui->rb32_2},
                              {ui->rb33_1,ui->rb33_2},
                              {ui->rb34_1,ui->rb34_2},
                              {ui->rb35_1,ui->rb35_2},
                              {ui->rb36_1,ui->rb36_2},
                              {ui->rb37_1,ui->rb37_2},
                              {ui->rb38_1,ui->rb38_2},
                              {ui->rb39_1,ui->rb39_2},
                              {ui->rb40_1,ui->rb40_2},
                              {ui->rb41_1,ui->rb41_2},
                              {ui->rb42_1,ui->rb42_2},
                              {ui->rb43_1,ui->rb43_2},
                              {ui->rb44_1,ui->rb44_2},
                              {ui->rb45_1,ui->rb45_2},
                              {ui->rb46_1,ui->rb46_2},
                              {ui->rb47_1,ui->rb47_2},
                              {ui->rb48_1,ui->rb48_2},
                              {ui->rb49_1,ui->rb49_2},
                              {ui->rb50_1,ui->rb50_2},
                              {ui->rb51_1,ui->rb51_2},
                              {ui->rb52_1,ui->rb52_2},
                              {ui->rb53_1,ui->rb53_2},
                              {ui->rb54_1,ui->rb54_2},
                              {ui->rb55_1,ui->rb55_2},
                              {ui->rb56_1,ui->rb56_2},
                              {ui->rb57_1,ui->rb57_2}
    };
    int q;
    QString res;

    while (query.next())
        id_people = query.value(0).toInt();
    if (id_people)
    {
        // Такая анкета уже есть, загружаем ее
        query.exec(QString("SELECT * FROM tbl_test1 WHERE f_people = %1 AND f_dt = '%2'").arg(id_people).arg(dt));
        while (query.next())
        {
            res = query.value(3).toString();
            for (int i = 0; i < 57; i++)
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
                }
            }
        }
    }
}

void Test1Dialog::accept(void)
{
    QSqlQuery query;
    QString legend1,
            legend2,
            legend3,
            sql,
            s_res;
    int id = 0;
    bool isFind = false;

    if (!calcRes(s_res))
        return;

    if (!id_people)
    {
//        // Сохраняем информацию о тестируемом
//        if (!query.exec(QString("INSERT INTO tbl_people (f_name,f_sex,f_age,f_height,f_weight) VALUES ('%1','%2',%3,%4,%5)").arg(name.toUpper()).arg(sex.toUpper()).arg(age).arg(height).arg(weight)))
//        {
//            qDebug() << query.lastError();
//            QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
//            return;
//        }

        query.exec(QString("SELECT id FROM tbl_people WHERE f_name = '%1' AND f_sex = '%2' AND f_age = %3").arg(name.toUpper()).arg(sex.toUpper()).arg(age));
        while (query.next())
            id_people = query.value(0).toInt();
    }

    // Сохраняем анекту
    query.exec(QString("SELECT id FROM tbl_test1 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        id = query.value(0).toInt();
        isFind = true;
    }
    if (isFind)
        sql = QString("UPDATE tbl_test1 SET f_res = '%1' WHERE f_people = %2 AND f_dt = '%3'").arg(s_res).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_test1 (f_people,f_dt,f_res) VALUES (%1,'%2','%3')").arg(id_people).arg(dt).arg(s_res);
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    // Определяем номер анкеты
    if (!id)
    {
        query.exec(QString("SELECT id FROM tbl_test1 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
        while (query.next())
            id = query.value(0).toInt();
    }
    getLegend(legend1,legend2,legend3);

    QMessageBox::information(this, tr("Результат"),tr("Результат тестування: %1, %2, %3").arg(legend1).arg(legend2).arg(legend3), QMessageBox::Ok);

    // Сохраняем результаты
    isFind = false;
    query.exec(QString("SELECT * FROM tbl_results WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
        isFind = true;
    if (isFind)
        sql = QString("UPDATE tbl_results SET f_id1 = %1,f_res11 = %2,f_legend11 = '%3',f_res12 = %4,f_legend12 = '%5',f_res13 = %6,f_legend13 = '%7' WHERE f_people = '%8' AND f_dt = '%9'").arg(id).arg(res1).arg(legend1).arg(res2).arg(legend2).arg(res3).arg(legend3).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_results (f_people,f_dt,f_id1,f_res11,f_legend11,f_res12,f_legend12,f_res13,f_legend13) VALUES (%1,'%2',%3,%4,'%5',%6,'%7',%8,'%9')").arg(id_people).arg(dt).arg(id).arg(res1).arg(legend1).arg(res2).arg(legend2).arg(res3).arg(legend3);
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    QDialog::accept();
}

bool Test1Dialog::calcRes(QString& s_res)
{
    bool isChoised;
    QRadioButton* rb[][2] = {
                              {ui->rb1_1,ui->rb1_2},
                              {ui->rb2_1,ui->rb2_2},
                              {ui->rb3_1,ui->rb3_2},
                              {ui->rb4_1,ui->rb4_2},
                              {ui->rb5_1,ui->rb5_2},
                              {ui->rb6_1,ui->rb6_2},
                              {ui->rb7_1,ui->rb7_2},
                              {ui->rb8_1,ui->rb8_2},
                              {ui->rb9_1,ui->rb9_2},
                              {ui->rb10_1,ui->rb10_2},
                              {ui->rb11_1,ui->rb11_2},
                              {ui->rb12_1,ui->rb12_2},
                              {ui->rb13_1,ui->rb13_2},
                              {ui->rb14_1,ui->rb14_2},
                              {ui->rb15_1,ui->rb15_2},
                              {ui->rb16_1,ui->rb16_2},
                              {ui->rb17_1,ui->rb17_2},
                              {ui->rb18_1,ui->rb18_2},
                              {ui->rb19_1,ui->rb19_2},
                              {ui->rb20_1,ui->rb20_2},
                              {ui->rb21_1,ui->rb21_2},
                              {ui->rb22_1,ui->rb22_2},
                              {ui->rb23_1,ui->rb23_2},
                              {ui->rb24_1,ui->rb24_2},
                              {ui->rb25_1,ui->rb25_2},
                              {ui->rb26_1,ui->rb26_2},
                              {ui->rb27_1,ui->rb27_2},
                              {ui->rb28_1,ui->rb28_2},
                              {ui->rb29_1,ui->rb29_2},
                              {ui->rb30_1,ui->rb30_2},
                              {ui->rb31_1,ui->rb31_2},
                              {ui->rb32_1,ui->rb32_2},
                              {ui->rb33_1,ui->rb33_2},
                              {ui->rb34_1,ui->rb34_2},
                              {ui->rb35_1,ui->rb35_2},
                              {ui->rb36_1,ui->rb36_2},
                              {ui->rb37_1,ui->rb37_2},
                              {ui->rb38_1,ui->rb38_2},
                              {ui->rb39_1,ui->rb39_2},
                              {ui->rb40_1,ui->rb40_2},
                              {ui->rb41_1,ui->rb41_2},
                              {ui->rb42_1,ui->rb42_2},
                              {ui->rb43_1,ui->rb43_2},
                              {ui->rb44_1,ui->rb44_2},
                              {ui->rb45_1,ui->rb45_2},
                              {ui->rb46_1,ui->rb46_2},
                              {ui->rb47_1,ui->rb47_2},
                              {ui->rb48_1,ui->rb48_2},
                              {ui->rb49_1,ui->rb49_2},
                              {ui->rb50_1,ui->rb50_2},
                              {ui->rb51_1,ui->rb51_2},
                              {ui->rb52_1,ui->rb52_2},
                              {ui->rb53_1,ui->rb53_2},
                              {ui->rb54_1,ui->rb54_2},
                              {ui->rb55_1,ui->rb55_2},
                              {ui->rb56_1,ui->rb56_2},
                              {ui->rb57_1,ui->rb57_2}
    };

    s_res = "";
    // Проверка на наличие ответов на все вопросы анкеты
    for (int i = 0; i < 57; i++)
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
        if (!isChoised)
        {
            QMessageBox::information(this, tr("Помилка"), tr("Не задана відповіднь на питання: %1!").arg(i + 1));
            return false;
        }
        // Екстраверсія
        if ((i == 0 || i == 2 || i == 8 || i == 10 || i == 12 || i == 16 || i == 21 || i == 24 || i ==  26 || i == 28 || i == 38 || i == 43 || i == 45 || i == 48 || i == 52 || i == 55) && rb[i][0]->isChecked())
            res1++;
        if ((i == 4 || i == 14 || i == 19 || i == 31 || i == 33 || i == 36 || i == 40 || i == 50) && rb[i][1]->isChecked())
            res1++;
        // Нейротизм
        if ((i == 1 || i == 3 || i == 6 || i == 8 || i == 10 || i == 13 || i == 15 || i == 18 || i == 20 || i == 22 || i == 25 || i == 27 || i == 30 || i == 32 || i == 35 || i == 37 || i == 39 || i == 42 || i == 44 || i == 46 || i == 49 || i == 51 || i == 54 || i == 56) && rb[i][0]->isChecked())
            res2++;
        // Відвертість
        if ((i == 5 || i == 23 || i == 35) && rb[i][0]->isChecked())
            res3++;
        if ((i == 11 || i == 17 || i == 29 || i == 41 || i ==  47 || i == 53) && rb[i][1]->isChecked())
            res3++;
    }
    return true;
}

void Test1Dialog::getLegend(QString& legend1,QString& legend2,QString& legend3)
{
    if (res1 <= 2)
        legend1 = "вкрай виражена інтроверсія";
    else if (res1 > 2 && res1 <= 7)
        legend1 = "виражена інтроверсія";
    else if (res1 > 7 && res1 <= 11)
        legend1 = "помірна інтроверсія";
    else if (res1 > 11 && res1 <= 15)
        legend1 = "помірна екстраверсія";
    else if (res1 > 15 && res1 <= 18)
        legend1 = "виражена екстраверсія";
    else if (res1 > 18)
        legend1 = "вкрай виражена екстраверсія";

    if (res2 <= 2)
        legend2 = "вкрай мало виражений нейротизм";
    else if (res2 > 2 && res2 <= 7)
        legend2 = "мало виражений нейротизм";
    else if (res2 > 7 && res2 <= 11)
        legend2 = "помірний нейротизм";
    else if (res2 > 11 && res2 <= 15)
        legend2 = "виражений нейротизм";
    else if (res2 > 15 && res2 <= 18)
        legend2 = "досить виражений нейротизм";
    else if (res2 > 18)
        legend2 = "вкрай виражений нейротизм";

    if (res3 <= 5)
        legend3 = "невідверті відповіді";
    else
        legend3 = "відверті відповіді";
}

void Test1Dialog::getResults(int& r1, int& r2, int& r3)
{
    r1 = res1;
    r2 = res2;
    r3 = res3;
}


