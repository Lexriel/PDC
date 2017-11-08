// $Id: filesystem_util.cpp 40 2010-07-16 22:04:49Z mgpensar $

#ifdef VISUAL_STUDIO
  #include "stdafx.h"
#endif

#include "filesystem_util.h"

namespace pensar_digital
{
    namespace cpplib
    {
        /// Pass INCLUDE_DIRS to the include_dirs parameter to include directories in the result.
        // Use this constant to improve code readability.
        const bool INCLUDE_DIRS        = true;

        /// Pass DO_NOT_INCLUDE_DIRS to the include_dirs parameter to not include directories in the result.
        // Use this constant to improve code readability.
        const bool DO_NOT_INCLUDE_DIRS = false;

        /// Pass RECURSIVE to the recursive parameter to read sub-directories recursively.
        // Use this constant to improve code readability.
        const bool RECURSIVE           = true;

        /// Pass NO_RECURSION to the recursive parameter to not read sub-directories.
        // Use this constant to improve code readability.
        const bool NO_RECURSION        = false;

        /// NO_FILTER means no regular expression should be applied as a filter.
        const std::string NO_FILTER    = "";
    }   // namespace cpplib
}       // namespace pensar_digital
