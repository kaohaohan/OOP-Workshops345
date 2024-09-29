#include "timeMonitor.h" 
#include <chrono>
#include "event.h"
namespace seneca{
    void TimeMonitor::startEvent(const char* name){
        m_startTime = std::chrono::steady_clock::now();
        m_eventName=name;
        m_startedEvent = true;
    }

    Event TimeMonitor::stopEvent(){
        //take the time when it ended
        auto endTime = std::chrono::steady_clock::now();
        //calculate the duration of the event
        std::chrono::steady_clock::duration duration = endTime - m_startTime;

    std::chrono::nanoseconds eventDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
     
      m_startedEvent = false;
      // create an instance of type Event and return it to the client.
      //不確定
    return Event(m_eventName.c_str(), eventDuration);
    }


}