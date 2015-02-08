#ifndef JSETTINGS_H
#define JSETTINGS_H

#include "jsoncons/json.hpp"


class JSettings
{
public:
    JSettings();
    ~JSettings();
    void test();
private:
    jsoncons::json settings;

};

#endif // JSETTINGS_H
