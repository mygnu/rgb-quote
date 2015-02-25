#include "ccvalues.hh"

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
        openAtStartup = settings.value("Application/openAtStartup").toBool();
        orderNumber = settings.value("cableCover/orderNumber").toInt();

        galvbond0_6KGPM = settings.value("cableCover/galvbond0_6KGPM").toDouble();
        galvbond1_6KGPM = settings.value("cableCover/galvbond1_6KGPM").toDouble();
        galvbond3_0KGPM = settings.value("cableCover/galvbond3_0KGPM").toDouble();

        flangesCharge = settings.value("cableCover/flangesCharge").toDouble();

        galvanisingPKG = settings.value("cableCover/galvanisingPKG").toDouble();
        sprayPanitPMS = settings.value("cableCover/sprayPanitPMS").toDouble();
        powderCotePMS = settings.value("cableCover/powderCotePMS").toDouble();

        galvbond0_6mmPrice = settings.value("cableCover/galvbond0_6mmPrice").toDouble();
        galvbond1_6mmPrice = settings.value("cableCover/galvbond1_6mmPrice").toDouble();
        galvbond3_0mmPrice = settings.value("cableCover/galvbond3_0mmPrice").toDouble();

        profitMargin = settings.value("cableCover/profitMargin").toDouble();

        openEndsPrice = settings.value("cableCover/openEndsPrice").toDouble();
        oneEndClosedPrice = settings.value("cableCover/oneEndClosedPrice").toDouble();
        bothEndsClosedPrice = settings.value("cableCover/bothEndsClosedPrice").toDouble();
    }
}

void CCValues::addOrder()
{
    settings.setValue("Application/orderNumber", ++orderNumber);
}
