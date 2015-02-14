#include "values.h"

Values::Values():
    settings(QSettings::IniFormat, QSettings::UserScope, "AppRgbQuote", "config")
{

}

Values::~Values()
{

}

