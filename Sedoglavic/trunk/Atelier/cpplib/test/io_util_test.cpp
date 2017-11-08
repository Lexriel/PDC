// $Id: io_util_test.cpp 9 2009-04-29 17:31:00Z mgpensar $

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <string>

#include <boost/test/unit_test.hpp>

#include "filesystem_util.h"
#include "io_util.h"
#include "my_boost.hpp"
#include "sys_user_info.h"

using namespace std;
using namespace boost::unit_test_framework;
namespace cpp = pensar_digital::cpplib;

BOOST_AUTO_TEST_SUITE(io_util_suite)

BOOST_AUTO_TEST_CASE(is_same_test)
{
    fs::path temp_dir = cpp::get_user_home () / "test_dir";
    fs::path file1 = temp_dir / "file_name";
    fs::path file2 = temp_dir / "dir" / "file_name";
    cpp::create_file (file1, "blah");
    cpp::create_file (file2, "blah");
    fs::last_write_time (file2, last_write_time (file1)); // Do timestamp file2 = timestamp file2.
    BOOST_CHECK (cpp::is_same (file1, file2));

    fs::last_write_time (file2, last_write_time (file1) + (time_t)60);
    BOOST_CHECK (! cpp::is_same (file1, file2));

    fs::path file3 = temp_dir / "file_name3";
    cpp::create_file (file3, "blah");

    BOOST_CHECK (cpp::is_same (file1, file3, cpp::SAME_SIZE + cpp::SAME_TIME));
}

BOOST_AUTO_TEST_SUITE_END ()
