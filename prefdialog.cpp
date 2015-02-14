#include <QVariant>
#include "prefdialog.h"
#include "ui_prefdialog.h"


PrefDialog::PrefDialog(Values &val, QWidget *parent) :
    QDialog(parent),
    values(&val),
    ui(new Ui::PrefDialog)
{
    ui->setupUi(this);
    setDefaults();
}

PrefDialog::~PrefDialog()
{
    delete ui;
}

void PrefDialog::setDefaults()
{

    QSettings &settings = values->settings;

    if(settings.contains("rgb/orderNumber"))
    {
        ui->orderNumberLineEdit->setText(settings.value("rgb/orderNumber").toString());
        ui->orderNumberLineEdit->setReadOnly(true);
    }
    else
    {

        settings.setValue("rgb/orderNumber", 10000);
    }
}
