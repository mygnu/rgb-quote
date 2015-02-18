#include <QVariant>
#include "prefdialog.h"
#include "ui_prefdialog.h"

#include <QDebug>
#include <QScroller>

PrefDialog::PrefDialog(Values &val, QWidget *parent) :
    QDialog(parent),
    values(&val),
    ui(new Ui::PrefDialog)
{
    ui->setupUi(this);
    loadValuesInGui();
    connect(ui->buttonBox, SIGNAL(accepted()),
            this, SLOT(onAccept()));
            QScroller::grabGesture(this, QScroller::TouchGesture);
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

    setDoubleValue(ui->kgFor0_6mmSB, "values/thick06mmKG");
    setDoubleValue(ui->kgFor1_6mmSB, "values/thick16mmKG");
    setDoubleValue(ui->kgFor3_0mmSB, "values/thick30mmKG");
    setDoubleValue(ui->flangesChargeSB, "values/flangesCharge");
    setDoubleValue(ui->galvaniseChargeSB, "values/galvPKG");

    setDoubleValue(ui->sprayPaintChargeSB, "values/sprayPaintPMS");
    setDoubleValue(ui->powderCoteChargeSB, "values/powderCotePMS");
    setDoubleValue(ui->priceFor0_6mmLE, "values/priceSheet06mm");
    setDoubleValue(ui->priceFor1_6mmLE, "values/priceSheet16mm");
    setDoubleValue(ui->priceFor3_0mmLE, "values/priceSheet30mm");
    setDoubleValue(ui->profitMarginLE, "values/profitMargin");
    setDoubleValue(ui->priceOneEndCloseSB, "values/priceOneEndClosed");
    setDoubleValue(ui->priceBothEndsClosedSB, "values/priceBothEndsClosed");

}

void PrefDialog::onAccept()
{
    saveValues();
    values->load();
 values->addOrder();
    qDebug() << values->orderNumber;
}

void PrefDialog::saveValues()
{
    QSettings &settings = values->settings;
    settings.setValue("this/edited", true);
    settings.setValue("values/thick06mmKG", ui->kgFor0_6mmSB->value());
    settings.setValue("values/thick16mmKG", ui->kgFor1_6mmSB->value());
    settings.setValue("values/thick30mmKG", ui->kgFor3_0mmSB->value());
    settings.setValue("values/flangesCharge", ui->flangesChargeSB->value());
    settings.setValue("values/galvPKG", ui->galvaniseChargeSB->value());
    settings.setValue("values/sprayPaintPMS", ui->sprayPaintChargeSB->value());
    settings.setValue("values/powderCotePMS", ui->powderCoteChargeSB->value());
    settings.setValue("values/priceSheet06mm", getDoubleValue(ui->priceFor0_6mmLE));
    settings.setValue("values/priceSheet16mm", getDoubleValue(ui->priceFor1_6mmLE));
    settings.setValue("values/priceSheet30mm", getDoubleValue(ui->priceFor3_0mmLE));
    settings.setValue("values/profitMargin", getDoubleValue(ui->profitMarginLE));
    settings.setValue("values/priceOneEndClosed", ui->priceOneEndCloseSB->value());
    settings.setValue("values/priceBothEndsClosed", ui->priceBothEndsClosedSB->value());
}

/**
 * return value from line edit if it has any
 * or return 1.0
 *
 */
double PrefDialog::getDoubleValue(QLineEdit *lineEdit)
{
    if(lineEdit->text().isEmpty())
    {
        return 1.0;
    }
    else
        return lineEdit->text().toDouble();
}

void PrefDialog::setDoubleValue(QLineEdit *le, QString name)
{
    if(values->settings.contains(name))
        le->setText(values->settings.value(name).toString());
    else
        le->setPlaceholderText("Set Value");
}

void PrefDialog::setDoubleValue(QDoubleSpinBox *sb, QString name)
{
    if(values->settings.contains(name))
        sb->setValue(values->settings.value(name).toDouble());
}
