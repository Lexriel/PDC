#ifndef ERROR_HPP_INCLUDED
#define ERROR_HPP_INCLUDED

#include <stdexcept>

#define INVALID_ARGUMENT(condition,message) \
    if (condition)\
    {\
        std::stringstream ss;\
        ss << __FILE__ << '\t' << __LINE__ << '\t' << message << std::endl;\
        std::cerr << ss.str ();\
        std::cerr.flush ();\
        throw std::invalid_argument (ss.str ());\
    };

#endif // ERROR_HPP_INCLUDED
