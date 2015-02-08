#include "prefdialog.h"
#include "ui_prefdialog.h"

PrefDialog::PrefDialog(QSettings &settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrefDialog)
{
    ui->setupUi(this);
    settings.setValue("mainwindow/size", parent->size());
}

PrefDialog::~PrefDialog()
{
    delete ui;
}
