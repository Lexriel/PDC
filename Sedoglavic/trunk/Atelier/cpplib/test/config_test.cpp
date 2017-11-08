// $Id$

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <boost/test/unit_test.hpp>

#include "config.h"
#include "dummy.h"
#include "string_util.h"

namespace cpp = pensar_digital::cpplib;
namespace tst = cpp::test;
namespace ser = cpp::serialization;

BOOST_AUTO_TEST_SUITE(config_suite)

BOOST_AUTO_TEST_CASE(config_test)
{
    std::vector<std::string> v;
    v.push_back ("a@a.com");
    v.push_back ("b@a.com");
    v.push_back ("c@a.com");
    tst::Dummy d ("teste", 1, v);

    const std::string K1 = "key1";
    const std::string K2 = "key2";
    const std::string K3 = "key3";

    cpp::Config<> cfg;
    cfg.set (K1, std::string("value1"), "Key 1");
    cfg.set (K2, "2");
    cfg.set<tst::Dummy> (K3, d);
    cfg.save ();

    cpp::Config<> cfg2;
    cfg2.load ();

    std::string p1;
    BOOST_CHECK(cfg2.get<std::string> (K1, p1));

    int p2;
    BOOST_CHECK(cfg2.get<int> (K2, p2));

    tst::Dummy d2;
    BOOST_CHECK(cfg2.get<tst::Dummy> (K3, d2));

    BOOST_CHECK_EQUAL ("value1", p1);
    BOOST_CHECK_EQUAL (2, p2);
    if (d == d2)
        BOOST_CHECK (1);
    else
        BOOST_CHECK (0);
}

BOOST_AUTO_TEST_CASE(config_xml_test)
{
    const std::string XML_FILE = "./test/config.xml";
    cpp::Config<std::string, boost::archive::xml_oarchive, boost::archive::xml_iarchive> cfg (XML_FILE);

    std::vector<std::string> v;
    v.push_back ("a@a.com");
    v.push_back ("b@a.com");
    v.push_back ("c@a.com");
    tst::Dummy d ("teste", 1, v);

    const std::string K1 = "key1";
    const std::string K2 = "key2";
    const std::string K3 = "key3";

    cfg.set (K1, std::string("value1"), "Key 1");
    cfg.set (K2, "2");
    cfg.set<tst::Dummy> (K3, d);
    cfg.save ();

    cpp::Config<std::string, boost::archive::xml_oarchive, boost::archive::xml_iarchive> cfg2 (XML_FILE);
    cfg2.load ();

    std::string p1;
    BOOST_CHECK(cfg2.get<std::string> (K1, p1));

    int p2;
    BOOST_CHECK(cfg2.get<int> (K2, p2));

    tst::Dummy d2;
    BOOST_CHECK(cfg2.get<tst::Dummy> (K3, d2));

    BOOST_CHECK_EQUAL ("value1", p1);
    BOOST_CHECK_EQUAL (2, p2);
    if (d == d2)
        BOOST_CHECK (1);
    else
        BOOST_CHECK (0);
}

/*
BOOST_AUTO_TEST_CASE(config_manager_stress_test)
{
    const std::string BIG_CFG = "big_cfg.txt";

    std::vector<std::string> v;
    v.push_back ("a@a.com");
    v.push_back ("b@a.com");
    v.push_back ("c@a.com");
    tst::Dummy d ("teste", 1, v);

    cpp::Config<> cfg (BIG_CFG);

    for (int i = 0; i < 10000; ++i)
    {
        cfg.set<tst::Dummy> (cpp::to_string(i), d);
    }
    cfg.save ();

    cpp::Config<> cfg2 (BIG_CFG);
    cfg2.load ();
    tst::Dummy d2;
    BOOST_CHECK(cfg2.get<tst::Dummy> ("9,999", d2));

    if (d == d2)
        BOOST_CHECK (1);
    else
        BOOST_CHECK (0);
}
*/

BOOST_AUTO_TEST_CASE(config_not_found_test)
{
    cpp::Config<> cfg;

    int i;
    BOOST_CHECK (! cfg.get<int> ("key", i));
}

BOOST_AUTO_TEST_CASE(config_file_not_found)
{
    // load checks if file exists so nothing should happen.
    cpp::Config<> cfg ("kh__.x");
}

BOOST_AUTO_TEST_CASE(config_corrupt_file_test)
{
    try
    {
        cpp::Config<> cfg ("./test/corrupt_DO_NOT_ERASE_THIS_TEST_FILE.txt");
        BOOST_FAIL("It was supposed to throw a boost::archive::archive_exception::exception_code::input_stream_error.");
    }
    catch (boost::archive::archive_exception& e)
    {
        BOOST_CHECK_EQUAL (e.code, boost::archive::archive_exception::exception_code::input_stream_error);
    }
}

BOOST_AUTO_TEST_SUITE_END ()
