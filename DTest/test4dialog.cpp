#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "test4dialog.h"
#include "ui_test4dialog.h"

Test4Dialog::Test4Dialog(QString d,QString n,QString s,int a,int h, int w,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test4Dialog)
{
    ui->setupUi(this);
    name = n;
    sex = s;
    age = a;
    height = h;
    weight = w;
    dt = d;
    id_people = 0;
    res = 0;

    setWindowTitle("Тест для выявления булимии - " + name);
    loadData();
}

Test4Dialog::~Test4Dialog()
{
    delete ui;
}

void Test4Dialog::loadData(void)
{
    QSqlQuery query(QString("SELECT id FROM tbl_people WHERE f_name = '%1' AND f_sex = '%2' AND f_age = %3").arg(name.toUpper()).arg(sex.toUpper()).arg(age));
    QRadioButton *rb[][6] = {
                              {ui->rb1_1,ui->rb1_2,NULL,NULL,NULL,NULL},
                              {ui->rb2_1,ui->rb2_2,NULL,NULL,NULL,NULL},
                              {ui->rb3_1,ui->rb3_2,NULL,NULL,NULL,NULL},
                              {ui->rb4_1,ui->rb4_2,NULL,NULL,NULL,NULL},
                              {ui->rb5_1,ui->rb5_2,NULL,NULL,NULL,NULL},
                              {ui->rb6_1,ui->rb6_2,ui->rb6_3,ui->rb6_4,ui->rb6_5,NULL},
                              {NULL,NULL,NULL,NULL,NULL,NULL},
                              {ui->rb8_1,ui->rb8_2,NULL,NULL,NULL,NULL},
                              {ui->rb9_1,ui->rb9_2,NULL,NULL,NULL,NULL},
                              {ui->rb10_1,ui->rb10_2,NULL,NULL,NULL,NULL},
                              {ui->rb11_1,ui->rb11_2,NULL,NULL,NULL,NULL},
                              {ui->rb12_1,ui->rb12_2,NULL,NULL,NULL,NULL},
                              {ui->rb13_1,ui->rb13_2,NULL,NULL,NULL,NULL},
                              {ui->rb14_1,ui->rb14_2,NULL,NULL,NULL,NULL},
                              {ui->rb15_1,ui->rb15_2,NULL,NULL,NULL,NULL},
                              {ui->rb16_1,ui->rb16_2,NULL,NULL,NULL,NULL},
                              {ui->rb17_1,ui->rb17_2,NULL,NULL,NULL,NULL},
                              {ui->rb18_1,ui->rb18_2,NULL,NULL,NULL,NULL},
                              {ui->rb19_1,ui->rb19_2,NULL,NULL,NULL,NULL},
                              {ui->rb20_1,ui->rb20_2,NULL,NULL,NULL,NULL},
                              {ui->rb21_1,ui->rb21_2,NULL,NULL,NULL,NULL},
                              {ui->rb22_1,ui->rb22_2,NULL,NULL,NULL,NULL},
                              {ui->rb23_1,ui->rb23_2,NULL,NULL,NULL,NULL},
                              {ui->rb24_1,ui->rb24_2,NULL,NULL,NULL,NULL},
                              {ui->rb25_1,ui->rb25_2,NULL,NULL,NULL,NULL},
                              {ui->rb26_1,ui->rb26_2,NULL,NULL,NULL,NULL},
                              {ui->rb27_1,ui->rb27_2,ui->rb27_3,ui->rb27_4,ui->rb27_5,ui->rb27_6},
                              {ui->rb28_1,ui->rb28_2,NULL,NULL,NULL,NULL},
                              {ui->rb29_1,ui->rb29_2,NULL,NULL,NULL,NULL},
                              {ui->rb30_1,ui->rb30_2,NULL,NULL,NULL,NULL},
                              {ui->rb31_1,ui->rb31_2,NULL,NULL,NULL,NULL},
                              {ui->rb32_1,ui->rb32_2,NULL,NULL,NULL,NULL},
                              {ui->rb33_1,ui->rb33_2,NULL,NULL,NULL,NULL}
    },
                *rb1[][7] = {
                        {ui->rb7_1_1, ui->rb7_1_2, ui->rb7_1_3, ui->rb7_1_4, ui->rb7_1_5, ui->rb7_1_6, ui->rb7_1_7},
                        {ui->rb7_2_1, ui->rb7_2_2, ui->rb7_2_3, ui->rb7_2_4, ui->rb7_2_5, ui->rb7_2_6, ui->rb7_2_7},
                        {ui->rb7_3_1, ui->rb7_3_2, ui->rb7_3_3, ui->rb7_3_4, ui->rb7_3_5, ui->rb7_3_6, ui->rb7_3_7},
                        {ui->rb7_4_1, ui->rb7_4_2, ui->rb7_4_3, ui->rb7_4_4, ui->rb7_4_5, ui->rb7_4_6, ui->rb7_4_7}
                       };
    int q;
    QString res;

    while (query.next())
        id_people = query.value(0).toInt();
    if (id_people)
    {
        // Такая анкета уже есть, загружаем ее
        query.exec(QString("SELECT * FROM tbl_test4 WHERE f_people = %1 AND f_dt = '%2'").arg(id_people).arg(dt));
        while (query.next())
        {
            for (int i = 0; i < 33; i++)
            {
                if (i == 6)
                {
                    res = query.value(4).toString();
                    for (int j = 0; j < 4; j++)
                    {
                        q = res.mid(j,1).toInt();
                        rb1[j][q - 1]->setChecked(true);
                    }
                    continue;
                }
                res = query.value(3).toString();
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
                    case 5:
                        rb[i][4]->setChecked(true);
                        break;
                    case 6:
                        rb[i][5]->setChecked(true);
                        break;
                }
            }
        }
    }
}

void Test4Dialog::accept(void)
{
    QSqlQuery query;
    QString legend,
            sql,
            s_res,
            s_res1;
    int id = 0;
    bool isFind = false;

    if (!calcRes(s_res,s_res1))
        return;

    if (!id_people)
    {
        // Сохраняем информацию о тестируемом
        if (!query.exec(QString("INSERT INTO tbl_people (f_name,f_sex,f_age,f_height,f_weight) VALUES ('%1','%2',%3,%4,%5)").arg(name.toUpper()).arg(sex.toUpper()).arg(age).arg(height).arg(weight)))
        {
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
            return;
        }

        query.exec(QString("SELECT id FROM tbl_people WHERE f_name = '%1' AND f_sex = '%2' AND f_age = %3").arg(name.toUpper()).arg(sex.toUpper()).arg(age));
        while (query.next())
            id_people = query.value(0).toInt();
    }

    // Сохраняем анекту
    query.exec(QString("SELECT id FROM tbl_test4 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        id = query.value(0).toInt();
        isFind = true;
    }
    if (isFind)
        sql = QString("UPDATE tbl_test4 SET f_res = '%1', f_res1 = '%2' WHERE f_people = %3 AND f_dt = '%4'").arg(s_res).arg(s_res1).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_test4 (f_people,f_dt,f_res,f_res1) VALUES (%1,'%2','%3','%4')").arg(id_people).arg(dt).arg(s_res).arg(s_res1);
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    // Определяем номер анкеты
    if (!id)
    {
        query.exec(QString("SELECT id FROM tbl_test4 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
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
        sql = QString("UPDATE tbl_results SET f_id4 = %1,f_res4 = %2,f_legend4 = '%3' WHERE f_people = '%4' AND f_dt = '%5'").arg(id).arg(res).arg(getLegend()).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_results (f_people,f_dt,f_id4,f_res4,f_legend4) VALUES (%1,'%2',%3,%4,'%5')").arg(id_people).arg(dt).arg(id).arg(res).arg(getLegend());
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    QDialog::accept();
}

bool Test4Dialog::calcRes(QString& s_res,QString& s_res1)
{
    bool isChoised;
    QRadioButton *rb[][6] = {
                              {ui->rb1_1,ui->rb1_2,NULL,NULL,NULL,NULL},
                              {ui->rb2_1,ui->rb2_2,NULL,NULL,NULL,NULL},
                              {ui->rb3_1,ui->rb3_2,NULL,NULL,NULL,NULL},
                              {ui->rb4_1,ui->rb4_2,NULL,NULL,NULL,NULL},
                              {ui->rb5_1,ui->rb5_2,NULL,NULL,NULL,NULL},
                              {ui->rb6_1,ui->rb6_2,ui->rb6_3,ui->rb6_4,ui->rb6_5,NULL},
                              {NULL,NULL,NULL,NULL,NULL,NULL},
                              {ui->rb8_1,ui->rb8_2,NULL,NULL,NULL,NULL},
                              {ui->rb9_1,ui->rb9_2,NULL,NULL,NULL,NULL},
                              {ui->rb10_1,ui->rb10_2,NULL,NULL,NULL,NULL},
                              {ui->rb11_1,ui->rb11_2,NULL,NULL,NULL,NULL},
                              {ui->rb12_1,ui->rb12_2,NULL,NULL,NULL,NULL},
                              {ui->rb13_1,ui->rb13_2,NULL,NULL,NULL,NULL},
                              {ui->rb14_1,ui->rb14_2,NULL,NULL,NULL,NULL},
                              {ui->rb15_1,ui->rb15_2,NULL,NULL,NULL,NULL},
                              {ui->rb16_1,ui->rb16_2,NULL,NULL,NULL,NULL},
                              {ui->rb17_1,ui->rb17_2,NULL,NULL,NULL,NULL},
                              {ui->rb18_1,ui->rb18_2,NULL,NULL,NULL,NULL},
                              {ui->rb19_1,ui->rb19_2,NULL,NULL,NULL,NULL},
                              {ui->rb20_1,ui->rb20_2,NULL,NULL,NULL,NULL},
                              {ui->rb21_1,ui->rb21_2,NULL,NULL,NULL,NULL},
                              {ui->rb22_1,ui->rb22_2,NULL,NULL,NULL,NULL},
                              {ui->rb23_1,ui->rb23_2,NULL,NULL,NULL,NULL},
                              {ui->rb24_1,ui->rb24_2,NULL,NULL,NULL,NULL},
                              {ui->rb25_1,ui->rb25_2,NULL,NULL,NULL,NULL},
                              {ui->rb26_1,ui->rb26_2,NULL,NULL,NULL,NULL},
                              {ui->rb27_1,ui->rb27_2,ui->rb27_3,ui->rb27_4,ui->rb27_5,ui->rb27_6},
                              {ui->rb28_1,ui->rb28_2,NULL,NULL,NULL,NULL},
                              {ui->rb29_1,ui->rb29_2,NULL,NULL,NULL,NULL},
                              {ui->rb30_1,ui->rb30_2,NULL,NULL,NULL,NULL},
                              {ui->rb31_1,ui->rb31_2,NULL,NULL,NULL,NULL},
                              {ui->rb32_1,ui->rb32_2,NULL,NULL,NULL,NULL},
                              {ui->rb33_1,ui->rb33_2,NULL,NULL,NULL,NULL}
    },
                *rb1[][7] = {
                        {ui->rb7_1_1, ui->rb7_1_2, ui->rb7_1_3, ui->rb7_1_4, ui->rb7_1_5, ui->rb7_1_6, ui->rb7_1_7},
                        {ui->rb7_2_1, ui->rb7_2_2, ui->rb7_2_3, ui->rb7_2_4, ui->rb7_2_5, ui->rb7_2_6, ui->rb7_2_7},
                        {ui->rb7_3_1, ui->rb7_3_2, ui->rb7_3_3, ui->rb7_3_4, ui->rb7_3_5, ui->rb7_3_6, ui->rb7_3_7},
                        {ui->rb7_4_1, ui->rb7_4_2, ui->rb7_4_3, ui->rb7_4_4, ui->rb7_4_5, ui->rb7_4_6, ui->rb7_4_7}
                       };

    s_res = s_res1 = "";
    // Проверка на наличие ответов на все вопросы анкеты
    for (int i = 0; i < 33; i++)
    {

        if (i == 6)
        {
            s_res += "0";
            for (int j = 0; j < 4; j++)
            {
                isChoised = false;
                for (int k = 0; k < 7; k++)
                    if (rb1[j][k]->isChecked())
                    {
                        isChoised = true;
                        s_res1 += QString("%1").arg(k + 1);
                        if (k > 0)
                            res += (k + 1);
                    }
            }
            if (!isChoised)
            {
                QMessageBox::information(this, tr("Помилка"), tr("Не задана відповіднь на питання: 7!"));
                return false;
            }
            continue;
        }


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
        else if (rb[i][4] && rb[i][4]->isChecked())
        {
            s_res += "5";
            isChoised = true;
        }
        else if (rb[i][5] && rb[i][5]->isChecked())
        {
            s_res += "6";
            isChoised = true;
        }
        if (!isChoised)
        {
            QMessageBox::information(this, tr("Помилка"), tr("Не задана відповіднь на питання: %1!").arg(i + 1));
            return false;
        }
        if ((i == 0 || i == 12 || i == 20 || i == 22 || i == 30) && rb[i][1]->isChecked())
            res++;
        if (!(i == 0 || i == 12 || i == 20 || i == 22 || i == 30) && rb[i][0]->isChecked())
            res++;
    }
    return true;
}

QString Test4Dialog::getLegend(void)
{
    QString legend;

    if (res < 10)
        legend = "низкий уровень";
    else if (res >= 10 && res <= 19)
        legend = "средний уровень";
    else if (res > 19)
        legend = "высокий уровень";
    return legend;
}

int Test4Dialog::getResults(void)
{
    return res;
}


