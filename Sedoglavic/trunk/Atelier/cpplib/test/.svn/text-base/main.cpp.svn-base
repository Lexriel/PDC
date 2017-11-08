#define BOOST_TEST_MODULE cpplib_test_string_util
#include "boost/test/included/unit_test.hpp"

#include <vector>
#include <string>
#include <map>

#include "..\string_util.h"

//____________________________________________________________________________//

using namespace std;
using namespace cpplib;

#define CHECK_EQUAL_COLLECTIONS(L, R)         \
  BOOST_CHECK_EQUAL_COLLECTIONS(L.begin (), L.end (), R.begin (), R.end ())

BOOST_AUTO_TEST_SUITE(string_util)

BOOST_AUTO_TEST_CASE(test_split)
{
	typedef map<string, vector<string> > Map;
	vector<string> v0, v1, v2;
	v0.push_back ("");
	v1.push_back ("blah");
	v2.push_back ("a");
	v2.push_back ("1");
	Map map;
	map[""      ] = v0;
	map["blah"  ] = v1;
	map["a, 1"   ] = v2;

	for (Map::iterator i = map.begin (); i != map.end (); ++i)
	{
		string s = i->first;
		vector<string> v;
		split (s, ',', &v);

		CHECK_EQUAL_COLLECTIONS(i->second, v);
	}

	v2[1] = " 1";
	vector<string> v;
	split ("a, 1", ',', &v, false);
	CHECK_EQUAL_COLLECTIONS (v2, v);
}
//---------------------------------------------------------------------------

BOOST_AUTO_TEST_CASE(test_remove_acentos)
{
	typedef map<string, string, less<string> > Map;
	Map map;
	map[""      ] = "";
	map["blah"  ] = "blah";
	map["José da Silva"  ] = "Jose da Silva";
	map["áàãäâ éèëê íìïî óòõöô úùüû ç"] = "aaaaa eeee iiii ooooo uuuu c";

	for (Map::iterator i = map.begin (); i != map.end (); ++i)
	{
		string s = i->first;
		string result  = remove_acentos (s);

		BOOST_CHECK_EQUAL (result, i->second);
	}
}
//---------------------------------------------------------------------------
BOOST_AUTO_TEST_SUITE_END()
