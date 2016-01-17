#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include "test3dialog.h"
#include "ui_test3dialog.h"

Test3Dialog::Test3Dialog(QString d,QString name,int id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test3Dialog)
{
    ui->setupUi(this);
    dt = d;
    id_people = id;
    res = 0;

    setWindowTitle("Шкала депрессии Бека - " + name);
    loadData();
}

Test3Dialog::~Test3Dialog()
{
    delete ui;
}

void Test3Dialog::loadData(void)
{
    QSqlQuery query;
    QRadioButton* rb[][4] = {
                              {ui->rb1_1,ui->rb1_2,ui->rb1_3,ui->rb1_4},
                              {ui->rb2_1,ui->rb2_2,ui->rb2_3,ui->rb2_4},
                              {ui->rb3_1,ui->rb3_2,ui->rb3_3,ui->rb3_4},
                              {ui->rb4_1,ui->rb4_2,ui->rb4_3,ui->rb4_4},
                              {ui->rb5_1,ui->rb5_2,ui->rb5_3,ui->rb5_4},
                              {ui->rb6_1,ui->rb6_2,ui->rb6_3,ui->rb6_4},
                              {ui->rb7_1,ui->rb7_2,ui->rb7_3,ui->rb7_4},
                              {ui->rb8_1,ui->rb8_2,ui->rb8_3,ui->rb8_4},
                              {ui->rb9_1,ui->rb9_2,ui->rb9_3,ui->rb9_4},
                              {ui->rb10_1,ui->rb10_2,ui->rb10_3,ui->rb10_4},
                              {ui->rb11_1,ui->rb11_2,ui->rb11_3,ui->rb11_4},
                              {ui->rb12_1,ui->rb12_2,ui->rb12_3,ui->rb12_4},
                              {ui->rb13_1,ui->rb13_2,ui->rb13_3,ui->rb13_4},
                              {ui->rb14_1,ui->rb14_2,ui->rb14_3,ui->rb14_4},
                              {ui->rb15_1,ui->rb15_2,ui->rb15_3,ui->rb15_4},
                              {ui->rb16_1,ui->rb16_2,ui->rb16_3,ui->rb16_4},
                              {ui->rb17_1,ui->rb17_2,ui->rb17_3,ui->rb17_4},
                              {ui->rb18_1,ui->rb18_2,ui->rb18_3,ui->rb18_4},
                              {ui->rb19_1,ui->rb19_2,ui->rb19_3,ui->rb19_4},
                              {ui->rb20_1,ui->rb20_2,ui->rb20_3,ui->rb20_4},
                              {ui->rb21_1,ui->rb21_2,ui->rb21_3,ui->rb21_4}
    };
    int q;
    QString res;

    query.exec(QString("SELECT * FROM tbl_test3 WHERE f_people = %1 AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        res = query.value(3).toString();
        for (int i = 0; i < 21; i++)
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

void Test3Dialog::accept(void)
{
    QSqlQuery query;
    QString sql,
            s_res;
    int id = 0;
    bool isFind = false;

    if (!calcRes(s_res))
        return;

    // Сохраняем анекту
    query.exec(QString("SELECT id FROM tbl_test3 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
    while (query.next())
    {
        id = query.value(0).toInt();
        isFind = true;
    }
    if (isFind)
        sql = QString("UPDATE tbl_test3 SET f_res = '%1' WHERE f_people = %2 AND f_dt = '%3'").arg(s_res).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_test3 (f_people,f_dt,f_res) VALUES (%1,'%2','%3')").arg(id_people).arg(dt).arg(s_res);
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    // Определяем номер анкеты
    if (!id)
    {
        query.exec(QString("SELECT id FROM tbl_test3 WHERE f_people = '%1' AND f_dt = '%2'").arg(id_people).arg(dt));
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
        sql = QString("UPDATE tbl_results SET f_id3 = %1,f_res3 = %2,f_legend3 = '%3' WHERE f_people = '%4' AND f_dt = '%5'").arg(id).arg(res).arg(getLegend()).arg(id_people).arg(dt);
    else
        sql = QString("INSERT INTO tbl_results (f_people,f_dt,f_id3,f_res3,f_legend3) VALUES (%1,'%2',%3,%4,'%5')").arg(id_people).arg(dt).arg(id).arg(res).arg(getLegend());
    if (!query.exec(sql))
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        qDebug() << query.lastError();
        return;
    }
    QDialog::accept();
}

bool Test3Dialog::calcRes(QString& s_res)
{
    bool isChoised;
    QRadioButton* rb[][4] = {
                              {ui->rb1_1,ui->rb1_2,ui->rb1_3,ui->rb1_4},
                              {ui->rb2_1,ui->rb2_2,ui->rb2_3,ui->rb2_4},
                              {ui->rb3_1,ui->rb3_2,ui->rb3_3,ui->rb3_4},
                              {ui->rb4_1,ui->rb4_2,ui->rb4_3,ui->rb4_4},
                              {ui->rb5_1,ui->rb5_2,ui->rb5_3,ui->rb5_4},
                              {ui->rb6_1,ui->rb6_2,ui->rb6_3,ui->rb6_4},
                              {ui->rb7_1,ui->rb7_2,ui->rb7_3,ui->rb7_4},
                              {ui->rb8_1,ui->rb8_2,ui->rb8_3,ui->rb8_4},
                              {ui->rb9_1,ui->rb9_2,ui->rb9_3,ui->rb9_4},
                              {ui->rb10_1,ui->rb10_2,ui->rb10_3,ui->rb10_4},
                              {ui->rb11_1,ui->rb11_2,ui->rb11_3,ui->rb11_4},
                              {ui->rb12_1,ui->rb12_2,ui->rb12_3,ui->rb12_4},
                              {ui->rb13_1,ui->rb13_2,ui->rb13_3,ui->rb13_4},
                              {ui->rb14_1,ui->rb14_2,ui->rb14_3,ui->rb14_4},
                              {ui->rb15_1,ui->rb15_2,ui->rb15_3,ui->rb15_4},
                              {ui->rb16_1,ui->rb16_2,ui->rb16_3,ui->rb16_4},
                              {ui->rb17_1,ui->rb17_2,ui->rb17_3,ui->rb17_4},
                              {ui->rb18_1,ui->rb18_2,ui->rb18_3,ui->rb18_4},
                              {ui->rb19_1,ui->rb19_2,ui->rb19_3,ui->rb19_4},
                              {ui->rb20_1,ui->rb20_2,ui->rb20_3,ui->rb20_4},
                              {ui->rb21_1,ui->rb21_2,ui->rb21_3,ui->rb21_4}
    };

    s_res = "";
    // Проверка на наличие ответов на все вопросы анкеты
    for (int i = 0; i < 21; i++)
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
            res += 1;
        }
        else if (rb[i][2]->isChecked())
        {
            s_res += "3";
            isChoised = true;
            res += 2;
        }
        else if (rb[i][3]->isChecked())
        {
            s_res += "4";
            isChoised = true;
            res += 3;
        }
        if (!isChoised)
        {
            QMessageBox::information(this, tr("Помилка"), tr("Не задана відповіднь на питання: %1!").arg(i + 1));
            return false;
        }
    }
    return true;
}

QString Test3Dialog::getLegend(void)
{
    QString legend;

    if (res <= 9)
        legend = "отсутствие депрессивных симптомов";
    else if (res > 9 && res <= 15)
        legend = "легкая депрессия (субдепрессия)";
    else if (res > 15 && res <= 19)
        legend = "умеренная депрессия";
    else if (res > 19 && res <= 29)
        legend = "выраженная депрессия (средней тяжести)";
    else if (res > 29)
        legend = "тяжёлая депрессия";
    return legend;
}

int Test3Dialog::getResults(void)
{
    return res;
}


