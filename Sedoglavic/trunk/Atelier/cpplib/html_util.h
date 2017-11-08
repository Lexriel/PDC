// $Id: html_util.h 40 2010-07-16 22:04:49Z mgpensar $

#ifndef html_utilH
#define html_utilH

#ifdef CODE_GEAR
#include <vcl.h>
#endif
#include <string>

namespace pensar_digital
{
    namespace cpplib
    {
        extern std::string escape_html (const std::string& s);
        extern std::string unescape_html (const std::string& s);
        #ifdef CODE_GEAR
        extern AnsiString escape_html (AnsiString s);
        extern AnsiString unescape_html (AnsiString s);
        #endif
        //extern template<class T> std::basic_string<T> escape_html   (const std::basic_string<T>& s);
        //extern template<typename T> std::basic_string<T> unescape_html (const std::basic_string<T>& s);
    }   // namespace cpplib
}       // namespace pensar_digital

#endif
