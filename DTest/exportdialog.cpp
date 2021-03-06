#include <QPushButton>
#include "exportdialog.h"
#include "ui_exportdialog.h"

ExportDialog::ExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);
    connect(ui->cbTest1, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbTest2, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbTest3, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbTest4, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbTest5, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbTest6, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbName, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbAge, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbSex, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbDate, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbLegend, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbResult, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbWeight, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
    connect(ui->cbHeight, SIGNAL(clicked(bool)), this, SLOT(slotCBClicked(bool)));
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::slotCBClicked(bool)
{
    bool isTest = ui->cbTest1->isChecked() || ui->cbTest2->isChecked() || ui->cbTest3->isChecked() || ui->cbTest4->isChecked() || ui->cbTest5->isChecked() || ui->cbTest6->isChecked(),
         isFields = ui->cbName->isChecked() || ui->cbSex->isChecked() || ui->cbDate->isChecked() || ui->cbAge->isChecked() || ui->cbResult->isChecked() || ui->cbLegend->isChecked() ||
                    ui->cbWeight->isChecked() || ui->cbHeight->isChecked();

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(isTest && isFields);
}

QMap<QString,bool> ExportDialog::getMap(void)
{
    QMap<QString,bool> map;

    map["Test1"] = ui->cbTest1->isChecked();
    map["Test2"] = ui->cbTest2->isChecked();
    map["Test3"] = ui->cbTest3->isChecked();
    map["Test4"] = ui->cbTest4->isChecked();
    map["Test5"] = ui->cbTest5->isChecked();
    map["Test6"] = ui->cbTest6->isChecked();

    map["Name"] = ui->cbName->isChecked();
    map["Age"] = ui->cbAge->isChecked();
    map["Sex"] = ui->cbSex->isChecked();
    map["Date"] = ui->cbDate->isChecked();
    map["Result"] = ui->cbResult->isChecked();
    map["Legend"] = ui->cbLegend->isChecked();
    map["Weight"] = ui->cbWeight->isChecked();
    map["Height"] = ui->cbHeight->isChecked();

    return map;
}
