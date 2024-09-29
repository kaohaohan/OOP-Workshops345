#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H


#include <iostream>
#include <string>

namespace seneca {

   struct Settings{
    bool m_show_all =false ;
    // default false
    bool m_verbose = false;
    //default nanoseconds
    std::string m_time_units= "nanoseconds";

   };
    extern Settings g_settings;
};

#endif