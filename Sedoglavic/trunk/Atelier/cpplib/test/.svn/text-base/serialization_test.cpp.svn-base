#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <boost/test/unit_test.hpp>

#include "serialization.hpp"
#include "dummy.h"

namespace cpp = pensar_digital::cpplib;
namespace ser = cpp::serialization;
namespace tst = cpp::test;

BOOST_AUTO_TEST_SUITE(serialization_suite)

BOOST_AUTO_TEST_CASE(serialization_test)
{
    std::vector<std::string> v;
    v.push_back ("a@a.com");
    v.push_back ("b@a.com");
    v.push_back ("c@a.com");
    tst::Dummy d ("teste", 1, v);

    std::string s;
    int i = 5;
    s = ser::to_string<int>(i);
    BOOST_CHECK_EQUAL (i, ser::from_string<int>(s));

    s = ser::to_string<tst::Dummy>(d);
    tst::Dummy d2 = ser::from_string<tst::Dummy>(s);
    if (d == d2)
        BOOST_CHECK (1);
    else
        BOOST_CHECK (0);
}

BOOST_AUTO_TEST_SUITE_END ()
