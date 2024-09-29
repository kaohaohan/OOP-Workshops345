#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H
#include "event.h"
#include <string>
#include <chrono>
#include <iostream>
namespace seneca {
    class Logger {
        //dma = array it points an address
        Event* m_event= nullptr;
        size_t m_size=0;
        public:
        //This class will not support copy operations -- disable them.
        Logger(const Logger&) =delete;
        Logger& operator=(const Logger&)=delete;


        Logger()=default;
        //destructor
        ~Logger();
        //move operations
        Logger(Logger&& other) noexcept;
        Logger& operator=(Logger&& other) noexcept;

        void addEvent(const Event& event);
        size_t size();
        void addSize();
        friend std::ostream& operator<<(std::ostream& os, const Logger& logger);

    };

}

#endif