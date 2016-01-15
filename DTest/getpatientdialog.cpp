#include <QTableWidgetItem>
#include <QSqlQuery>
#include <QCompleter>
#include <QStringList>
#include <QPushButton>
#include "getpatientdialog.h"
#include "ui_getpatientdialog.h"

GetPatientDialog::GetPatientDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetPatientDialog)
{
    ui->setupUi(this);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    ui->deDate->setDateTime(QDateTime::currentDateTime());
    connect(ui->tableWidget->selectionModel(), SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this, SLOT(slotEnabledBtn(QItemSelection, QItemSelection)));

    initDialog();
}

GetPatientDialog::~GetPatientDialog()
{
    delete ui;
}

QString GetPatientDialog::getName(void)
{
    return ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text();
}

QString GetPatientDialog::getSex(void)
{
    return ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text();
}

int GetPatientDialog::getAge(void)
{
    return ui->tableWidget->item(ui->tableWidget->currentRow(),2)->text().toInt();
}

QString GetPatientDialog::getDate(void)
{
    return ui->deDate->text();
}

int GetPatientDialog::getID(void)
{
    return ui->tableWidget->item(ui->tableWidget->currentRow(),5)->text().toInt();
}

int GetPatientDialog::getHeight(void)
{
    return ui->tableWidget->item(ui->tableWidget->currentRow(),3)->text().toInt();
}

int GetPatientDialog::getWeight(void)
{
    return ui->tableWidget->item(ui->tableWidget->currentRow(),4)->text().toInt();
}

void GetPatientDialog::slotEnabledBtn(QItemSelection, QItemSelection)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(ui->tableWidget->selectionModel()->hasSelection());
}

void GetPatientDialog::initDialog(void)
{
    QSqlQuery query;
    int current = 0;

    ui->tableWidget->setFocus();
    while (ui->tableWidget->rowCount())
        ui->tableWidget->removeRow(0);
    if (query.exec(QString("SELECT DISTINCT f_name, f_sex, f_age, f_height, f_weight, id FROM tbl_people ORDER BY f_name")))
        while (query.next())
        {
            ui->tableWidget->insertRow(current);
            for (int i = 0; i < 6; i++)
            {
                ui->tableWidget->setItem(current, i, new QTableWidgetItem(query.value(i).toString()));
                ui->tableWidget->item(current,i)->setFlags((Qt::ItemFlags)~Qt::ItemIsEditable);
            }
        }
    ui->tableWidget->setColumnWidth(0,260);
    ui->tableWidget->setColumnWidth(1,50);
    ui->tableWidget->setColumnWidth(2,50);
    ui->tableWidget->setColumnWidth(3,50);
    ui->tableWidget->setColumnWidth(4,50);
    ui->tableWidget->setColumnHidden(5,true);

}

