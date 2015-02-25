#include <QVariant>
#include "prefdialog.hh"
#include "ui_prefdialog.h"

#include <QDebug>
#include <QScroller>

CCPrefDialog::CCPrefDialog(CCValues &val, QWidget *parent) :
    QDialog(parent),
    values(&val),
    ui(new Ui::PrefDialog)
{
    ui->setupUi(this);
    loadValuesInGui();

    connect(ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(onAccept()));

    QScroller::grabGesture(this, QScroller::TouchGesture);
    setWindowModality(Qt::WindowModal);
    ui->tabWidget->setCurrentIndex(0);
}

CCPrefDialog::~CCPrefDialog()
{
    delete ui;
}

void CCPrefDialog::loadValuesInGui()
{

    QSettings &settings = values->settings;
    ui->openAtStartup->setChecked(settings.value("this/openAtStartup").toBool());
    if(settings.contains("values/orderNumber"))
    {
        ui->orderNumberLineEdit->setPlaceholderText(settings.value("values/orderNumber").toString());
        ui->orderNumberLineEdit->setReadOnly(true);
    }
    else
        settings.setValue("values/orderNumber", 10000);

    setDoubleValue(ui->kgFor0_6mmSB, "values/thick06mmKG");
    setDoubleValue(ui->kgFor1_6mmSB, "values/thick16mmKG");
    setDoubleValue(ui->kgFor3_0mmSB, "values/thick30mmKG");
    setDoubleValue(ui->flangesChargeSB, "values/flangesCharge");
    setDoubleValue(ui->galvaniseChargeSB, "values/galvPKG");

    setDoubleValue(ui->sprayPaintChargeSB, "values/sprayPaintPMS");
    setDoubleValue(ui->powderCoteChargeSB, "values/powderCotePMS");
    setDoubleValue(ui->priceFor0_6mmSB, "values/priceSheet06mm");
    setDoubleValue(ui->priceFor1_6mmSB, "values/priceSheet16mm");
    setDoubleValue(ui->priceFor3_0mmSB, "values/priceSheet30mm");
    setDoubleValue(ui->profitMarginSB, "values/profitMargin");
    setDoubleValue(ui->priceOpenEndsSB, "value/priceOpenEnds");
    setDoubleValue(ui->priceOneEndCloseSB, "values/priceOneEndClosed");
    setDoubleValue(ui->priceBothEndsClosedSB, "values/priceBothEndsClosed");

}

void CCPrefDialog::onAccept()
{
    saveValues();
    values->load();
}

void CCPrefDialog::saveValues()
{
    QSettings &settings = values->settings;
    settings.setValue("this/edited", true);
    if(ui->openAtStartup->isChecked())
        settings.setValue("this/openAtStartup", true);
    else
        settings.setValue("this/openAtStartup", false);

    settings.setValue("values/thick06mmKG", ui->kgFor0_6mmSB->value());
    settings.setValue("values/thick16mmKG", ui->kgFor1_6mmSB->value());
    settings.setValue("values/thick30mmKG", ui->kgFor3_0mmSB->value());
    settings.setValue("values/flangesCharge", ui->flangesChargeSB->value());
    settings.setValue("values/galvPKG", ui->galvaniseChargeSB->value());
    settings.setValue("values/sprayPaintPMS", ui->sprayPaintChargeSB->value());
    settings.setValue("values/powderCotePMS", ui->powderCoteChargeSB->value());
    settings.setValue("values/priceSheet06mm", ui->priceFor0_6mmSB->value());
    settings.setValue("values/priceSheet16mm", ui->priceFor1_6mmSB->value());
    settings.setValue("values/priceSheet30mm", ui->priceFor3_0mmSB->value());
    settings.setValue("values/profitMargin", ui->profitMarginSB->value());
    settings.setValue("values/priceOpenEnds", ui->priceOpenEndsSB->value());
    settings.setValue("values/priceOneEndClosed", ui->priceOneEndCloseSB->value());
    settings.setValue("values/priceBothEndsClosed", ui->priceBothEndsClosedSB->value());
}



void CCPrefDialog::setDoubleValue(QLineEdit *le, QString name)
{
    if(values->settings.contains(name))
        le->setText(values->settings.value(name).toString());
    else
        le->setPlaceholderText("Set Value");
}

void CCPrefDialog::setDoubleValue(QDoubleSpinBox *sb, QString name)
{
    if(values->settings.contains(name))
        sb->setValue(values->settings.value(name).toDouble());
}
