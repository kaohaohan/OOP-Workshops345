#include "logger.h"
using namespace std;

namespace seneca{

     Logger::~Logger(){
        if(m_event!=nullptr){
            delete[] m_event;
            m_event = nullptr;
        }
     }
        //move cons
     Logger::Logger(Logger&& other)noexcept{
        // call move operator 
          *this = std::move(other);
     }


    Logger &Logger::operator=(Logger&& other)noexcept{
        if(this != &other){
            delete[] m_event; 
            m_event=other.m_event;
            m_size=other.m_size;
            other.m_event=nullptr;
            other.m_size =0;
        }
        return *this;
    }
    size_t Logger::size(){
        return m_size;
    }

     void Logger::addSize(){
        m_size ++;
     }
    void Logger::addEvent(const Event& event){
        //new an Event pointer
        Event *e =new Event[m_size+1];
        for (size_t i=0;i<m_size;i++){
            e[i]= m_event[i];
        }
        e[m_size]=event;
        delete[] m_event;
        m_event = e;

        //updated size
       m_size ++;
        
    }

        std::ostream& operator<<(std::ostream& os, const Logger& logger) {
        for (size_t i = 0; i < logger.m_size; ++i) {
            os << logger.m_event[i] << std::endl;
        }
        return os;
    }

}
