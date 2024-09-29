#ifndef SENECA_TIMEMONITOR_H
#define SENECA_TIMEMONITOR_H


#include "event.h" 
#include <iostream>
#include <chrono>  

namespace seneca {
   class TimeMonitor{

    std::string m_eventName;
    //Accronding startEvent() needs event started and the name of the event.
    std::chrono::steady_clock::time_point m_startTime;
     bool m_startedEvent = false; 

    public:

    void startEvent(const char* name);
    Event stopEvent();

   };
};

#endif