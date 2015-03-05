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

#include "values.hh"

CCValues::CCValues():
    settings(QSettings::IniFormat, QSettings::UserScope, "rgbQuoteApp", "config")
{

}

CCValues::~CCValues()
{

}

void CCValues::load()
{
    if(settings.contains("Application/edited") && settings.value("Application/edited").toBool())
    {
        orderNumber = settings.value("cableCover/orderNumber").toInt();
        openAtStartup = settings.value("Application/openAtStartup").toBool();

        openEndsPrice = settings.value("cableCover/openEndsPrice").toDouble();
        oneEndClosedPrice = settings.value("cableCover/oneEndClosedPrice").toDouble();
        bothEndsClosedPrice = settings.value("cableCover/bothEndsClosedPrice").toDouble();

        flangesCharge = settings.value("cableCover/flangesCharge").toDouble();

        galvanisingPKG = settings.value("cableCover/galvanisingPKG").toDouble();
        sprayPanitPMS = settings.value("cableCover/sprayPanitPMS").toDouble();
        powderCotePMS = settings.value("cableCover/powderCotePMS").toDouble();

        galvanisingMin = settings.value("cableCover/galvanisingMin").toDouble();
        sprayPanitMin = settings.value("cableCover/sprayPanitMin").toDouble();
        powderCoteMin = settings.value("cableCover/powderCoteMin").toDouble();

        galvbond0_6mmPrice = settings.value("cableCover/galvbond0_6mmPrice").toDouble();
        galvbond1_6mmPrice = settings.value("cableCover/galvbond1_6mmPrice").toDouble();
        galvbond3_0mmPrice = settings.value("cableCover/galvbond3_0mmPrice").toDouble();

        galvbond0_6KGPM = settings.value("cableCover/galvbond0_6KGPM").toDouble();
        galvbond1_6KGPM = settings.value("cableCover/galvbond1_6KGPM").toDouble();
        galvbond3_0KGPM = settings.value("cableCover/galvbond3_0KGPM").toDouble();

        profitMargin = settings.value("cableCover/profitMargin").toDouble();

    }
}

void CCValues::addOrder()
{
    settings.setValue("Application/orderNumber", ++orderNumber);
}
