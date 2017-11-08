// $Id: sys_user_info.h 40 2010-07-16 22:04:49Z mgpensar $

#ifndef sys_user_infoH
#define sys_user_infoH
//---------------------------------------------------------------------------

#include <string>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

namespace pensar_digital
{
    namespace cpplib
    {
        void getUserName (std::string* s);

        /// Gets user home directory.
        fs::path get_user_home ();
    }   // namespace cpplib
}       // namespace pensar_digital
#endif
