#include "jsettings.h"

JSettings::JSettings()
{
   settings = jsoncons::json::parse_file("settings.conf");
}

JSettings::~JSettings()
{

}

