#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <iostream>
#include <fstream>
#include <string>

namespace pensar_digital
{
    namespace cpplib
    {
        // Comment the line below to exclude logging from the compiled file.
        #define LOG_ON
        #define CODEGEAR_BUG

        #ifdef LOG_ON
            extern std::ofstream _log;
            extern const char* LOG_FILE_NAME;
            extern bool log_on;
            inline void enable_log  () {if (! _log.is_open ()) _log.open (LOG_FILE_NAME); log_on = true;}
            inline void disable_log () {_log.close (); log_on = false;}

            // Comment the line below if you do not want the log to show where the message was originated.
            #define SHOW_LOCAL
            #define LOCAL  __FILE__ << "\t linha " << __LINE__ << "\t"

            // The name was changed from log to cpp log to avoid conflict with math.h log function.
            #ifdef SHOW_LOCAL
                #define cpplog if (pensar_digital::cpplib::log_on) pensar_digital::cpplib::_log << LOCAL
            #else
                #define cpplog if (pensar_digital::cpplib::log_on) pensar_digital::cpplib::_log
            #endif
            #define LOG(msg) cpplog << msg << std::endl; pensar_digital::cpplib::_log.flush ();
            #define LOG_FLUSH pensar_digital::cpplib::_log.flush ();
        #else
            #ifndef CODEGEAR_BUG
                #define cpplog \/\/
                #define LOG \/\/
                #define LOG_FLUSH \/\/
            #else
                #define cpplog if (0) std::cout
                #define LOG if (0)
                #define LOG_FLUSH ;
            #endif
        #endif
    }   // namespace cpplib
}       // namespace pensar_digital

#endif // LOG_H_INCLUDED

