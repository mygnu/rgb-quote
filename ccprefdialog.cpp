#include <QVariant>
#include "ccprefdialog.hh"
#include "ui_ccprefdialog.h"

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
    ui->openAtStartup->setChecked(settings.value("Application/openAtStartup").toBool());

    if(!settings.contains("Application/orderNumber"))
        settings.setValue("Application/orderNumber", 10000);
    else
        ui->orderNumberLE->setPlaceholderText(settings.value("Application/orderNumber").toString());

    ui->orderNumberLE->setReadOnly(true);

    setDoubleValue(ui->openEndsPriceSB, "cableCover/openEndsPrice");
    setDoubleValue(ui->oneEndClosedPriceSB, "cableCover/oneEndClosedPrice");
    setDoubleValue(ui->bothEndsClosedPriceSB, "cableCover/bothEndsClosedPrice");

    setDoubleValue(ui->flangesChargeSB, "cableCover/flangesCharge");

    setDoubleValue(ui->galvanisingPKG_SB, "cableCover/galvanisingPKG");
    setDoubleValue(ui->sprayPaintPMS_SB, "cableCover/sprayPanitPMS");
    setDoubleValue(ui->powderCotePMS_SB, "cableCover/powderCotePMS");

    setDoubleValue(ui->galvanisingMinSB, "cableCover/galvanisingMin");
    setDoubleValue(ui->sprayPaintMinSB, "cableCover/sprayPanitMin");
    setDoubleValue(ui->powderCoteMinSB, "cableCover/powderCoteMin");

    setDoubleValue(ui->galvbond0_6mmPriceSB, "cableCover/galvbond0_6mmPrice");
    setDoubleValue(ui->galvbond1_6mmPriceSB, "cableCover/galvbond1_6mmPrice");
    setDoubleValue(ui->galvbond3_0mmPriceSB, "cableCover/galvbond3_0mmPrice");

    setDoubleValue(ui->profitMarginSB, "cableCover/profitMargin");

//    setDoubleValue(ui->priceFor0_6mmSB, "cableCover/priceSheet06mm");
//    setDoubleValue(ui->priceFor1_6mmSB, "cableCover/priceSheet16mm");
//    setDoubleValue(ui->priceFor3_0mmSB, "cableCover/priceSheet30mm");

}

void CCPrefDialog::onAccept()
{
    saveValues();
    values->load();
}

void CCPrefDialog::saveValues()
{
    QSettings &settings = values->settings;
    settings.setValue("Application/edited", true);
    if(ui->openAtStartup->isChecked())
        settings.setValue("Application/openAtStartup", true);
    else
        settings.setValue("Application/openAtStartup", false);

    settings.setValue("cableCover/openEndsPrice", ui->openEndsPriceSB->value());
    settings.setValue("cableCover/oneEndClosedPrice", ui->oneEndClosedPriceSB->value());
    settings.setValue("cableCover/bothEndsClosedPrice", ui->bothEndsClosedPriceSB->value());


    settings.setValue("cableCover/flangesCharge", ui->flangesChargeSB->value());

    settings.setValue("cableCover/galvanisingPKG", ui->galvanisingPKG_SB->value());
    settings.setValue("cableCover/sprayPanitPMS", ui->sprayPaintPMS_SB->value());
    settings.setValue("cableCover/powderCotePMS", ui->powderCotePMS_SB->value());

    settings.setValue("cableCover/galvanisingMin", ui->galvanisingMinSB->value());
    settings.setValue("cableCover/sprayPanitMin", ui->sprayPaintMinSB->value()) ;
    settings.setValue("cableCover/powderCoteMin", ui->powderCoteMinSB->value());

    settings.setValue("cableCover/galvbond0_6mmPrice", ui->galvbond0_6mmPriceSB->value());
    settings.setValue("cableCover/galvbond1_6mmPrice", ui->galvbond1_6mmPriceSB->value());
    settings.setValue("cableCover/galvbond3_0mmPrice", ui->galvbond3_0mmPriceSB->value());

    settings.setValue("cableCover/profitMargin", ui->profitMarginSB->value());

    //    settings.setValue("cableCover/galvbond0_6KGPM", ui->g);
    //    settings.setValue("cableCover/galvbond1_6KGPM");
    //    settings.setValue("cableCover/galvbond3_0KGPM");
    //    settings.setValue("cableCover/galvbond0_6mmPrice");
    //    settings.setValue("cableCover/galvbond1_6mmPrice");
    //    settings.setValue("cableCover/galvbond3_0mmPrice");



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
