#include "values.h"

Values::Values():
    settings(QSettings::IniFormat, QSettings::UserScope, "AppRgbQuote", "config")
{

}

Values::~Values()
{

}

void Values::load()
{
    if(settings.contains("this/edited") && settings.value("this/edited").toBool())
    {
        orderNumber = settings.value("values/orderNumber").toInt();

        thick0_6mmKG = settings.value("values/thick06mmKG").toDouble();
        thick1_6mmKG = settings.value("values/thick16mmKG").toDouble();
        thick3_0mmKG = settings.value("values/thick30mmKG").toDouble();
        flangesCharge = settings.value("values/flangesCharge").toDouble();
        galvanisingPKG = settings.value("values/galvPKG").toDouble();
        sprayPanitPMS = settings.value("values/sprayPaintPMS").toDouble();
        powderCotePMS = settings.value("values/powderCotePMS").toDouble();
        priceSheet0_6mm = settings.value("values/priceSheet06mm").toDouble();
        priceSheet1_6mm = settings.value("values/priceSheet16mm").toDouble();
        priceSheet3_0mm = settings.value("values/priceSheet30mm").toDouble();
        profitMargin = settings.value("values/profitMargin").toDouble();
        oneEndClosed = settings.value("values/priceOneEndClosed").toDouble();
        bothEndsClosed = settings.value("values/priceBothEndsClosed").toDouble();
    }
}

void Values::addOrder()
{
    settings.setValue("values/orderNumber", ++orderNumber);
}
