// $Id: io_util.h 40 2010-07-16 22:04:49Z mgpensar $

#ifndef io_utilH
#define io_utilH

#include <string>
#ifdef WINDOWS
#include <io.h>
#endif

#include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;

namespace pensar_digital
{
    namespace cpplib
    {
        // Constantes usadas em is_same ().
        extern const int SAME_NAME;
        extern const int SAME_SIZE;
        extern const int SAME_TIME;
        extern const int SAME_ALL;

        #ifdef BORLAND
        extern bool operator == (const std::ftime& left, const std::ftime& right);
        extern bool operator != (const std::ftime& left, const std::ftime& right);
        extern bool operator <  (const std::ftime& left, const std::ftime& right);
        extern std::ftime fileTimestamp (const char* gridFilePath);
        extern std::string fileTimestampString (const char* gridFilePath);
        #endif

        //extern long long get_file_size(const char* sFileName);
        extern bool can_read (const char* file_name);

        #ifdef WIN32
        extern __int64 get_file_size (const std::string& file_name);
        #endif

        /// Verifies if the file has the same name, size and timestamp.
        extern bool is_same (const fs::path& p1, const fs::path& p2, const int compare_mask = SAME_ALL);

        extern bool file_exists (std::string filename);
    }   // namespace cpplib
}       // namespace pensar_digital
#endif