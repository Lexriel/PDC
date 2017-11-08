// $Id$

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <boost/test/unit_test.hpp>

#include "algorithm_util.h"
#include <map>
#include <string>

typedef std::pair<int, std::string> MapEntry;
struct IsDigit : public std::unary_function<MapEntry, bool>
{
  bool operator() (MapEntry p) {return isdigit (p.second[0]);}
};

typedef std::map<int, std::string> Map;

struct EqualToOne : public std::unary_function<MapEntry, bool>
{
  bool operator() (int i) {return i == 1;}
};

namespace pd = pensar_digital::cpplib;

BOOST_AUTO_TEST_SUITE(algorithm_util_suite)

BOOST_AUTO_TEST_CASE(erase_if_map)
{
	Map map;
	map[0] = "a";
	map[1] = "1";
	map[2] = "c";

    //cpplib::erase_if<Map::key_type, Map::mapped_type, Map::key_compare, Map::allocator_type, std::map, IsDigit> (map, IsDigit());
    pd::erase_if (map, IsDigit());

    BOOST_CHECK_EQUAL ("a", map[0]);
	BOOST_CHECK_EQUAL ("c", map[2]);
	BOOST_CHECK_EQUAL (2u  , map.size ());
}

BOOST_AUTO_TEST_CASE(erase_if)
{
	std::vector<int> v(3);
	v[0] = 0;
	v[1] = 1;
	v[2] = 2;

    pd::erase_if (v, std::bind2nd(std::equal_to<int>(), 1));

    BOOST_CHECK_EQUAL (0, v[0]);
	BOOST_CHECK_EQUAL (2, v[1]);
	BOOST_CHECK_EQUAL (2u, v.size ());
}

BOOST_AUTO_TEST_SUITE_END ()

