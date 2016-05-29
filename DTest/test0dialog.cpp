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
    id_people = 0;
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
bool Test0Dialog::checkData(void)
{
    bool isOk;

    if (ui->leName->text().simplified().isEmpty())
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Не задано прізвище пацієнта!"), QMessageBox::Ok);
        return false;
    }
    ui->leHeight->text().toInt(&isOk);
    if (!isOk)
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Не корректно задан зріст пацієнта!"), QMessageBox::Ok);
        return false;
    }
    ui->leWeight->text().toInt(&isOk);
    if (!isOk)
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Не корректно задана вага пацієнта!"), QMessageBox::Ok);
        return false;
    }
    ui->leBalancing->text().toInt(&isOk);
    if (!isOk)
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Не корректно задана статична балансировка!"), QMessageBox::Ok);
        return false;
    }
    ui->leHolding->text().toInt(&isOk);
    if (!isOk)
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Не корректно задана затримка дихання!"), QMessageBox::Ok);
        return false;
    }
    ui->leMaxWeight->text().toInt(&isOk);
    if (!isOk)
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Не корректно задана максимальна вага пацієнта!"), QMessageBox::Ok);
        return false;
    }
    ui->leMinWeight->text().toInt(&isOk);
    if (!isOk)
    {
        QMessageBox::critical(this, tr("Помилка"),tr("Не корректно задана мінімальна вага пацієнта!"), QMessageBox::Ok);
        return false;
    }
    return true;
}

void Test0Dialog::setCBValue(QComboBox* cb,QString text)
{
    int i = 0;

    for (; i < cb->count(); i++)
        if (cb->itemText(i) == text)
        {
            cb->setCurrentIndex(i);
            return;
        }
    cb->addItem(text);
    cb->setCurrentIndex(cb->count() - 1);
}

void Test0Dialog::setCBValueImpact(QString text)
{
    QString qw[] = {
                     "не влияет",
                     "влияет на физическую деятельность",
                     "на выполнение професиональных обязанностей",
                     "психологический дискомфорт",
                     "нарушение социального общения",
                     "на общение с противоположным полом",
                     "на сексуальный комфорт",
                     "на состояние здоровья"
                   };


    ui->cbImpact->clear();
    for (int i = 0; i < 8; i++)
        ui->cbImpact->addItem(qw[i], text.indexOf(qw[i]) != -1 ? QVariant(true) : QVariant(false));
}

void Test0Dialog::initDialog(int id)
{
    QSqlQuery query;

    id_people = id;
    initDialog();
    query.exec(QString("SELECT * FROM tbl_people WHERE id = %1").arg(id));
    while (query.next())
    {
        ui->leName->setText(query.value(1).toString());
        ui->cbSex->setCurrentIndex((query.value(2).toString().toUpper() == "МУЖ.") ? 0 : 1);
        ui->sbAge->setValue(query.value(3).toInt());
        ui->leHeight->setText(query.value(4).toString());
        ui->leWeight->setText(query.value(5).toString());
        ui->sbADs->setValue(query.value(6).toInt());
        ui->sbADd->setValue(query.value(7).toInt());
        ui->leBalancing->setText(query.value(8).toString());
        ui->leHolding->setText(query.value(9).toString());
        setCBValue(ui->cbMerried,query.value(10).toString());
        setCBValue(ui->cbProfit,query.value(11).toString());
        setCBValue(ui->cbEducation,query.value(12).toString());
        setCBValue(ui->cbStatus,query.value(13).toString());
        setCBValue(ui->cbDiseases,query.value(14).toString());
        setCBValue(ui->cbBad,query.value(15).toString());
        setCBValue(ui->cbViolation,query.value(16).toString());
        setCBValue(ui->cbMedication,query.value(17).toString());
        setCBValue(ui->cbNumber,query.value(18).toString());
        setCBValue(ui->cbObesity,query.value(19).toString());
        setCBValue(ui->cbOverweight,query.value(20).toString());
        setCBValue(ui->cbDuration,query.value(21).toString());
        setCBValue(ui->cbCause,query.value(22).toString());
        setCBValue(ui->cbLifestyle,query.value(23).toString());
        setCBValue(ui->cbAttempts,query.value(24).toString());
        setCBValue(ui->cbEffect,query.value(25).toString());
        ui->leMaxWeight->setText(query.value(26).toString());
        ui->leMinWeight->setText(query.value(27).toString());
        setCBValueImpact(query.value(28).toString());
        setCBValue(ui->cbWant,query.value(29).toString());
        setCBValue(ui->cbReady,query.value(30).toString());
//        ui->cbMerried->setCurrentText(query.value(10).toString());
//        ui->cbProfit->setCurrentText(query.value(11).toString());
//        ui->cbEducation->setCurrentText(query.value(12).toString());
//        ui->cbStatus->setCurrentText(query.value(13).toString());
//        ui->cbDiseases->setCurrentText(query.value(14).toString());
//        ui->cbBad->setCurrentText(query.value(15).toString());
//        ui->cbViolation->setCurrentText(query.value(16).toString());
//        ui->cbMedication->setCurrentText(query.value(17).toString());
//        ui->cbNumber->setCurrentText(query.value(18).toString());
//        ui->cbObesity->setCurrentText(query.value(19).toString());
//        ui->cbOverweight->setCurrentText(query.value(20).toString());
//        ui->cbDuration->setCurrentText(query.value(21).toString());
//        ui->cbCause->setCurrentText(query.value(22).toString());
//        ui->cbLifestyle->setCurrentText(query.value(23).toString());
//        ui->cbAttempts->setCurrentText(query.value(24).toString());
//        ui->cbEffect->setCurrentText(query.value(25).toString());
//        ui->leMaxWeight->setText(query.value(26).toString());
//        ui->leMinWeight->setText(query.value(27).toString());
//        ui->cbImpact->setCurrentText(query.value(28).toString());
//        ui->cbWant->setCurrentText(query.value(29).toString());
//        ui->cbReady->setCurrentText(query.value(30).toString());
    }
}

QString Test0Dialog::getName(void)
{
    return ui->leName->text();
}

QString Test0Dialog::getSex(void)
{
    return ui->cbSex->currentText();
}

int Test0Dialog::getAge(void)
{
    return ui->sbAge->value();
}

int Test0Dialog::getHeight(void)
{
    return ui->leHeight->text().toInt();
}

int Test0Dialog::getWeight(void)
{
    return ui->leWeight->text().toInt();
}

void Test0Dialog::accept(void)
{
    QSqlQuery query;
    QString name = ui->leName->text().toUpper().simplified(),
            sex = ui->cbSex->currentText(),
            merried = ui->cbMerried->currentText(),
            profit = ui->cbProfit->currentText(),
            education = ui->cbEducation->currentText(),
            status = ui->cbStatus->currentText(),
            diseases = ui->cbDiseases->currentText(),
            bad = ui->cbBad->currentText(),
            violation = ui->cbViolation->currentText(),
            medication = ui->cbMedication->currentText(),
            number = ui->cbNumber->currentText(),
            obesity = ui->cbObesity->currentText(),
            overweight = ui->cbOverweight->currentText(),
            duration = ui->cbDuration->currentText(),
            cause = ui->cbCause->currentText(),
            lifestyle = ui->cbLifestyle->currentText(),
            attempts = ui->cbAttempts->currentText(),
            effect = ui->cbEffect->currentText(),
//            impact = ui->cbImpact->currentText(),
            impact = ui->cbImpact->getDisplayText(),
            want = ui->cbWant->currentText(),
            ready = ui->cbReady->currentText();
    int age = ui->sbAge->text().toInt(),
        height = ui->leHeight->text().toInt(),
        weight = ui->leWeight->text().toInt(),
        ads = ui->sbADs->text().toInt(),
        add = ui->sbADd->text().toInt(),
        balancing = ui->leBalancing->text().toInt(),
        holding = ui->leHolding->text().toInt(),
        maxweight = ui->leMaxWeight->text().toInt(),
        minweight = ui->leMinWeight->text().toInt();

    // Проверка введенных данных
    if (!checkData())
        return;


    // Сохраняем информацию о тестируемом
    if (!id_people)
    {
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
    }
    else
    {
        if (!query.exec(QString("UPDATE tbl_people SET f_name='%1',f_sex='%2',f_age=%3,f_height=%4,f_weight=%5,f_ads=%6,f_add=%7,f_balancing=%8,f_holding=%9,f_merried='%10',f_profit='%11', \
                                                       f_education='%12',f_status='%13',f_diseases='%14',f_bad='%15',f_violation='%16',f_medication='%17',f_number='%18',f_obesity='%19',\
                                                       f_overweight='%20', f_duration='%21',f_cause='%22',f_lifestyle='%23',f_attempts='%24',f_effect='%25',f_maxweight=%26,f_minweight=%27,\
                                                       f_impact='%28',f_want='%29',f_ready='%30' \
                                                       WHERE id=%31") \
                                                         .arg(name).arg(sex).arg(age).arg(height).arg(weight).arg(ads).arg(add).arg(balancing).arg(holding).arg(merried).arg(profit) \
                                                         .arg(education).arg(status).arg(diseases).arg(bad).arg(violation).arg(medication).arg(number).arg(obesity).arg(overweight) \
                                                         .arg(duration).arg(cause).arg(lifestyle).arg(attempts).arg(effect).arg(maxweight).arg(minweight).arg(impact).arg(want)\
                                                         .arg(ready).arg(id_people)))

        {
            qDebug() << query.lastError();
            QMessageBox::critical(this, tr("Помилка"),tr("Помилка запису бази даних!"), QMessageBox::Ok);
            return;
        }
    }
    QDialog::accept();
}
