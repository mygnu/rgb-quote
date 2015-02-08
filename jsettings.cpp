#include "jsettings.h"

JSettings::JSettings()
{
   settings = jsoncons::json::parse_file("settings.conf");
}

JSettings::~JSettings()
{

}

void JSettings::test()
{
    std::ifstream is("settings.conf");
    if (!is.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    jsoncons::json_deserializer handler;
    jsoncons::json_reader reader(is, handler);
    while (!reader.eof())
    {
        reader.read();
        if (!reader.eof())
        {
            jsoncons::json val = std::move(handler.root());
            std::cout << val << std::endl;
        }
    }
}
