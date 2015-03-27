/*
* Copyright © 2015 Mygnu <me@mygnu.net>
*
*
*
* This file is part of rgb-quote.
*
* rgb-quote is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Final Term is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with rgb-quote. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QVariant>
#include "ccprefs.hh"
#include "ui_prefdialog.h"

#include <QDebug>
#include <QScroller>

CCPrefs::CCPrefs(QWidget *parent, Values *val) :
    QDialog(parent),
    values(val),
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

CCPrefs::~CCPrefs()
{
    delete ui;
}

void CCPrefs::loadValuesInGui()
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

    setDoubleValue(ui->galvbond0_6KGPM_SB, "cableCover/galvbond0_6KGPM");
    setDoubleValue(ui->galvbond1_6KGPM_SB, "cableCover/galvbond1_6KGPM");
    setDoubleValue(ui->galvbond3_0KGPM_SB, "cableCover/galvbond3_0KGPM");


}

void CCPrefs::onAccept()
{
    saveValues();
    values->load_cc_values();
}

void CCPrefs::saveValues()
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

    settings.setValue("cableCover/galvbond0_6KGPM", ui->galvbond0_6KGPM_SB->value());
    settings.setValue("cableCover/galvbond1_6KGPM", ui->galvbond1_6KGPM_SB->value());
    settings.setValue("cableCover/galvbond3_0KGPM", ui->galvbond3_0KGPM_SB->value());





}



void CCPrefs::setDoubleValue(QLineEdit *le, QString name)
{
    if(values->settings.contains(name))
        le->setText(values->settings.value(name).toString());
    else
        le->setPlaceholderText("Set Value");
}

void CCPrefs::setDoubleValue(QDoubleSpinBox *sb, QString name)
{
    if(values->settings.contains(name))
        sb->setValue(values->settings.value(name).toDouble());
}
