#include <QVariant>
#include "prefdialog.h"
#include "ui_prefdialog.h"

#include <QDebug>

PrefDialog::PrefDialog(Values &val, QWidget *parent) :
    QDialog(parent),
    values(&val),
    ui(new Ui::PrefDialog)
{
    ui->setupUi(this);
    loadValuesInGui();
    connect(ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(onAccept()));
}

PrefDialog::~PrefDialog()
{
    delete ui;
}

void PrefDialog::loadValuesInGui()
{

    QSettings &settings = values->settings;

    if(settings.contains("values/orderNumber"))
    {
        ui->orderNumberLineEdit->setPlaceholderText(settings.value("values/orderNumber").toString());
        ui->orderNumberLineEdit->setReadOnly(true);
    }
    else
        settings.setValue("values/orderNumber", 10000);


    if(settings.contains("values/thick06mmKG"))
    {
        ui->kgFor0_6mmLE->setText(settings.value("values/thick06mmKG").toString());
    }

    if(settings.contains("values/thick16mmKG"))
    {
        ui->kgFor1_6mmLE->setText(settings.value("values/thick16mmKG").toString());
    }

    if(settings.contains("values/thick30mmKG"))
    {
        ui->kgFor3_0mmLE->setText(settings.value("values/thick30mmKG").toString());
    }
}

void PrefDialog::onAccept()
{

    saveValues();
    values->load();

    qDebug() << "on Accept" << values->thick0_6mmKG;
}

void PrefDialog::saveValues()
{
    QSettings &settings = values->settings;
    settings.setValue("values/thick06mmKG", checkLineEdit(ui->kgFor0_6mmLE));
    settings.setValue("values/thick16mmKG", checkLineEdit(ui->kgFor1_6mmLE));
    settings.setValue("values/thick30mmKG", checkLineEdit(ui->kgFor3_0mmLE));
}

double PrefDialog::checkLineEdit(QLineEdit *lineEdit)
{
    if(lineEdit->text().isEmpty())
    {
        return 1.0;
    }
    else
        return lineEdit->text().toDouble();
}
