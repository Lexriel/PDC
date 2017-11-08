// $Id$

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <map>
#include <vector>
#include <boost/test/unit_test.hpp>

#include "log.h"
#include "distance.hpp"
#include "my_boost.hpp"

namespace pd = pensar_digital::cpplib;

BOOST_AUTO_TEST_SUITE(distance_suite)

BOOST_AUTO_TEST_CASE(distance_test)
{
    using std::string;
    typedef std::pair<string, string> spair;
	typedef std::map<std::pair<std::string, std::string>, int> Map;
	Map map;
	map[spair ("", "") ] = 0;
	map[spair ("", "a")] = 1;
	map[spair ("abc", "abd")] = 1;
	map[spair ("abc", "ab")] = 1;
	map[spair ("abc", "acb")] = 1;
	map[spair ("abc", "a")] = 2;
	map[spair ("abc", "acd")] = 2;
	map[spair ("abc", "agg")] = 2;
	map[spair ("Campeonato Inglês Arsenal x Liverpool", "Campeonato Ingles ArsenalxLiverpool")] = 3;
	map[spair ("1234", "456")] = 4;
	map[spair ("PLANETA EXPN: SURFE 2009", "PLANETA EXPN : AVENTURAS COM RENATA FALZONI")] = 25;
    map[spair ("Copa América Masculino de Basquete: Brasil x Porto Rico", "Copa América (r)  Masculino de Basquete -VT- Brasil x Porto Rico")] = 10;
    map[spair ("copaamericamasculinodebasquetebrasilxportorico", "copaamericamasculinodebasqueteVTbrasilxportorico")] = 2;

	for (Map::iterator i = map.begin (); i != map.end (); ++i)
	{
		string s = i->first.first;
		string t = i->first.second;
		int result  = pd::distance (s, t);
        //std::cout << "<" << s << ", " << t << ">" << std::endl;
		BOOST_CHECK_EQUAL (result, i->second);
	}
}

BOOST_AUTO_TEST_CASE(min_distance_test)
{
    std::vector<std::string> v;
    v.push_back ("abcdef");
    v.push_back ("abcde");
    v.push_back ("abcd");
    v.push_back ("abc");
    v.push_back ("ab");
    v.push_back ("a");
    v.push_back ("");

    std::string s = pd::min_distance<> ("ab c", v);
    BOOST_CHECK_EQUAL ("abc", s);
}

BOOST_AUTO_TEST_CASE(min_distance2_test)
{
    std::vector<std::string> v;
    v.push_back ("abcdef");
    v.push_back ("abcde");
    v.push_back ("abcd");
    v.push_back ("abc");
    v.push_back ("ab");
    v.push_back ("a");
    v.push_back ("");

    std::vector<std::string> expected;
    expected.push_back ("abc");
    expected.push_back ("abcd");
    expected.push_back ("ab");
    expected.push_back ("abcde");
    expected.push_back ("a");
    expected.push_back ("abcdef");
    expected.push_back ("");

    std::vector<std::string> result;

    pd::min_distance<> ("ab c", v, result);

    CHECK_EQUAL_COLLECTIONS (expected, result);

    std::vector<std::string> expected2;
    expected2.push_back ("abc");
    expected2.push_back ("abcd");
    expected2.push_back ("ab");

    expected2.push_back ("abcde");
    expected2.push_back ("a");
    //expected2.push_back ("abcdef");
    //expected2.push_back ("");

    std::vector<std::string> result2;

    pd::min_distance<> ("ab c", v, result2, 5);

    CHECK_EQUAL_COLLECTIONS (expected2, result2);
}

BOOST_AUTO_TEST_CASE(min_distance_map_test)
{
    typedef std::map<std::string, std::string> PMap;
    PMap pmap;
    pmap["pacote Resid"] = "residencial";
    pmap["pacote Col"  ] = "coletivo";
    pmap["pacote Hotel"] = "hotel";

    PMap::value_type min = pd::min_distance_map_key<std::string, PMap> ("Coletivo", pmap);

    BOOST_CHECK_EQUAL ("coletivo", min.second);
}

BOOST_AUTO_TEST_CASE(min_distance_map_test2)
{
    typedef std::map<std::string, std::string> PMap;
    PMap pmap;
    pmap["pacote Resid"] = "residencial";
    pmap["pacote Col"  ] = "coletivo";
    pmap["pacote Hotel"] = "hotel";

    PMap::value_type min = pd::min_distance_map_key<std::string, PMap> ("Coletivo", pmap, 1u);

    BOOST_CHECK_EQUAL ("", min.second);
}

BOOST_AUTO_TEST_SUITE_END ()
