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
    thick0_6mmKG = settings.value("values/thick06mmKG").toDouble();

}
