#include "event.h"
#include "settings.h"
#include <iomanip>

namespace seneca{
    //constructor
    Event:: Event(const char* name, const std::chrono::nanoseconds& duration):m_name(name), m_duration(duration){};

     std::ostream& operator<<(std::ostream& os, const Event& e){
          // local-to-function variable that remains in memory for the lifetime of the program
            static int counter=0;
            ++counter;
            os << std::right << std::setw(2) << counter << ": "
            << std::setw(40)<< e.m_name <<" -> ";
                
           int width = 11; // default nanoseconds width
    if (g_settings.m_time_units == "seconds") {
        width = 2;
    } else if (g_settings.m_time_units == "milliseconds") {
        width = 5;
    } else if (g_settings.m_time_units == "microseconds") {
        width = 8;
    }

    os << std::setw(width) << std::right;

    if (g_settings.m_time_units == "seconds") {
        os << std::chrono::duration_cast<std::chrono::seconds>(e.m_duration).count();
    } else if (g_settings.m_time_units == "milliseconds") {
        os << std::chrono::duration_cast<std::chrono::milliseconds>(e.m_duration).count();
    } else if (g_settings.m_time_units == "microseconds") {
        os << std::chrono::duration_cast<std::chrono::microseconds>(e.m_duration).count();
    } else {
        os << e.m_duration.count();
    }

    os << " " << g_settings.m_time_units;

    return os;
             
};


}