#include "prefdialog.h"
#include "ui_prefdialog.h"

PrefDialog::PrefDialog(QSettings &settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrefDialog)
{
    ui->setupUi(this);
    jsettings.test();
    //settings.setValue("Item1/width/test", 68);
}

PrefDialog::~PrefDialog()
{
    delete ui;
}
