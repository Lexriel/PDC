// $Id$

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <boost/test/unit_test.hpp>

#include "time_util.h"

namespace pd = pensar_digital::cpplib;

BOOST_AUTO_TEST_SUITE(time_util_suite)

BOOST_AUTO_TEST_CASE(stimestamp_test)
{
    std::string s = "2009-10-09 20:40:22";
    time_t t = pd::sdatetime2time_t (s);
    std::string s1 = pd::stimestamp (t);
    BOOST_CHECK_EQUAL (s, s1);

    std::string s2 = pd::stimestamp ();
    cout << s2 << std::endl;
}

BOOST_AUTO_TEST_CASE(today_test)
{
    std::string stoday = pd::today ();
    std::cout << stoday << std::endl;

    std::string stoday2 = pd::today ("%m%y");
    std::cout << stoday2 << std::endl;
}

BOOST_AUTO_TEST_SUITE_END ()
