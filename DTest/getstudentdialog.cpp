#include <QSqlQuery>
#include <QCompleter>
#include <QStringList>
#include <QPushButton>
#include "getstudentdialog.h"
#include "ui_getstudentdialog.h"

GetStudentDialog::GetStudentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetStudentDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->deDate->setDateTime(QDateTime::currentDateTime());
    connect(ui->leName, SIGNAL(textChanged(const QString&)), this, SLOT(slotChangeText(const QString&)));

    initDialog();
}

GetStudentDialog::~GetStudentDialog()
{
    delete ui;
}

QString GetStudentDialog::getName(void)
{
    return ui->leName->text();
}

QString GetStudentDialog::getSex(void)
{
    return ui->cbSex->currentText();
}

int GetStudentDialog::getAge(void)
{
    return ui->sbAge->text().toInt();
}

QString GetStudentDialog::getDate(void)
{
    return ui->deDate->text();
}

int GetStudentDialog::getHeight(void)
{
    return ui->leHeight->text().toInt();
}

int GetStudentDialog::getWeight(void)
{
    return ui->leWeight->text().toInt();
}

void GetStudentDialog::slotChangeText(const QString&)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->leName->text().length());
}

void GetStudentDialog::initDialog(void)
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
//    ui->leName->setText("");
}

void GetStudentDialog::initDialog(QString name,QString sex,int age,int height, int weight, QString dt)
{
    initDialog();
    ui->leName->setText(name);
    ui->cbSex->setCurrentIndex((sex == "ЧОЛ.") ? 0 : 1);
    ui->sbAge->setValue(age);
    ui->leHeight->setText(QString("%1").arg(height));
    ui->leWeight->setText(QString("%1").arg(weight));
    ui->deDate->setDateTime(QDateTime::fromString(dt,"dd.MM.yyyy"));
}
