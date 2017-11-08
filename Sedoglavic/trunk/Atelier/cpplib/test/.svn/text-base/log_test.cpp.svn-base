// $Id$

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <boost/test/unit_test.hpp>

#include "log.h"
#include "io_util.h"
#include "filesystem_util.h"

namespace pd = pensar_digital::cpplib;

BOOST_AUTO_TEST_SUITE(log_suite)

BOOST_AUTO_TEST_CASE(log_test)
{
    #ifdef LOG_ON

    cpplog << "Extremely simple log is cool " << std::endl;
    cpplog << "and efficient." << std::endl;

    std::ifstream ifs ("log.txt");
    BOOST_CHECK (ifs.is_open ());

    ifs.close ();
    pd::disable_log ();

    fs::path p1 ("log.txt");
    fs::path p2 ("log2.txt");
    fs::remove (p2);
    fs::copy_file (p1, p2);
    fs::remove (p1);

    cpplog << "nope";
    BOOST_CHECK(! pd::file_exists ("log.txt"));

    pd::enable_log ();
    cpplog << "nope";
    BOOST_CHECK(pd::file_exists ("log.txt"));

    #endif
}

BOOST_AUTO_TEST_SUITE_END ()
