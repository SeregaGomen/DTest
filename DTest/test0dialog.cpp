#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QSqlError>
#include <QPushButton>
#include <QCompleter>
#include "test0dialog.h"
#include "ui_test0dialog.h"

Test0Dialog::Test0Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Test0Dialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    connect(ui->leName, SIGNAL(textChanged(const QString&)), this, SLOT(slotChangeText(const QString&)));

    initDialog();
}

Test0Dialog::~Test0Dialog()
{
    delete ui;
}

void Test0Dialog::slotChangeText(const QString&)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->leName->text().length());
}

void Test0Dialog::initDialog(void)
{
    QSqlQuery query;
    QCompleter *completer1;
    QStringList nameList;

    ui->leName->setFocus();


    if (query.exec(QString("SELECT DISTINCT f_name FROM tbl_people ORDER BY f_name")))
    {
        while (query.next())
            nameList << query.value(0).toString();

        completer1 = new QCompleter(nameList);
        completer1->setMaxVisibleItems(5);
        completer1->setCaseSensitivity(Qt::CaseInsensitive);
        ui->leName->setCompleter(completer1);
    }
}

//!!!! Проверить корректность ввода данных (тип и обязательные поля)

void Test0Dialog::accept(void)
{
    QSqlQuery query;
    QString name = ui->leName->text().toUpper().simplified(),
            sex = ui->cbSex->currentText().toUpper().simplified(),
            merried = ui->cbMerried->currentText().toUpper().simplified(),
            profit = ui->cbProfit->currentText().toUpper().simplified(),
            education = ui->cbEducation->currentText().toUpper().simplified(),
            status = ui->cbStatus->currentText().toUpper().simplified(),
            diseases = ui->cbDiseases->currentText().toUpper().simplified(),
            bad = ui->cbBad->currentText().toUpper().simplified(),
            violation = ui->cbViolation->currentText().toUpper().simplified(),
            medication = ui->cbMedication->currentText().toUpper().simplified(),
            number = ui->cbNumber->currentText().toUpper().simplified(),
            obesity = ui->cbObesity->currentText().toUpper().simplified(),
            overweight = ui->cbOverweight->currentText().toUpper().simplified(),
            duration = ui->cbDuration->currentText().toUpper().simplified(),
            cause = ui->cbCause->currentText().toUpper().simplified(),
            lifestyle = ui->cbLifestyle->currentText().toUpper().simplified(),
            attempts = ui->cbAttempts->currentText().toUpper().simplified(),
            effect = ui->cbEffect->currentText().toUpper().simplified(),
            impact = ui->cbImpact->currentText().toUpper().simplified(),
            want = ui->cbWant->currentText().toUpper().simplified(),
            ready = ui->cbReady->currentText().toUpper().simplified();
    int age = ui->sbAge->text().toInt(),
        height = ui->leHeight->text().toInt(),
        weight = ui->leWeight->text().toInt(),
        ads = ui->sbADs->text().toInt(),
        add = ui->sbADd->text().toInt(),
        balancing = ui->leBalancing->text().toInt(),
        holding = ui->leHolding->text().toInt(),
        maxweight = ui->leMaxWeight->text().toInt(),
        minweight = ui->leMinWeight->text().toInt();

    // Сохраняем информацию о тестируемом
    if (!query.exec(QString("INSERT INTO tbl_people (f_name,f_sex,f_age,f_height,f_weight,f_ads,f_add,f_balancing,f_holding,f_merried,f_profit,f_education,f_status, \
                                                     f_diseases,f_bad,f_violation,f_medication,f_number,f_obesity,f_overweight, f_duration,f_cause,f_lifestyle, f_attempts, \
                                                     f_effect,f_maxweight,f_minweight,f_impact,f_want,f_ready) \
                                                     VALUES ('%1','%2',%3,%4,%5,%6,%7,%8,%9,'%10','%11','%12','%13','%14','%15','%16','%17','%18','%19','%20','%21','%22','%23', \
                                                             '%24','%25',%26,%27,'%28','%29','%30')") \
                                                     .arg(name).arg(sex).arg(age).arg(height).arg(weight).arg(ads).arg(add).arg(balancing).arg(holding).arg(merried).arg(profit) \
                                                     .arg(education).arg(status).arg(diseases).arg(bad).arg(violation).arg(medication).arg(number).arg(obesity).arg(overweight) \
                                                     .arg(duration).arg(cause).arg(lifestyle).arg(attempts).arg(effect).arg(maxweight).arg(minweight).arg(impact).arg(want).arg(ready)))
    {
        qDebug() << query.lastError();
        QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
        return;
    }
    QDialog::accept();
}

//void GetPatientDialog::initDialog(QString name,QString sex,int age,int height, int weight, QString dt)
//{
//    initDialog();
//    ui->leName->setText(name);
//    ui->cbSex->setCurrentIndex((sex == "Муж.") ? 0 : 1);
//    ui->sbAge->setValue(age);
//    ui->leHeight->setText(QString("%1").arg(height));
//    ui->leWeight->setText(QString("%1").arg(weight));
//    ui->deDate->setDateTime(QDateTime::fromString(dt,"dd.MM.yyyy"));
//}
