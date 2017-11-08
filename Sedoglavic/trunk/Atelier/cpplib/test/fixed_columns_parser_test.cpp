// $Id: fixed_columns_parser_test.cpp 40 2010-07-16 22:04:49Z mgpensar $

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <boost/test/unit_test.hpp>

#include "fixed_columns_parser.h"
#include <boost/fusion/include/at_c.hpp>
#include <cmath>
//_____________________________________________________________________________


using namespace std;
namespace cpp = pensar_digital::cpplib;
using namespace boost::fusion;

const string line = "15213MARCOS DA SILVA BRASILEIRO                      RUA RUA RUA RUA RUA RU                   765   APTO 23                POMPEIA                SAO PAULO              SP   05617000                                   ";

BOOST_AUTO_TEST_SUITE(fixed_columns_parser_suite)

BOOST_AUTO_TEST_CASE(parse_test)
{
	cpp::FixedColumnsParser<int, string, int> parser (4, 10, 2);
	cpp::FixedColumnsParser<int, string, int>::ParseResult r = parser.parse("0123abcdefgh  18");

	BOOST_CHECK_EQUAL (123,          at_c<0>(r));
	BOOST_CHECK_EQUAL ("abcdefgh  ", at_c<1>(r));
	BOOST_CHECK_EQUAL (18,           at_c<2>(r));

	typedef cpp::FixedColumnsParser<char, short, int, long, long long, float, double, long double, string, bool> Parser;
	Parser parser2 (1, 1, 1, 1, 1, 1, 1, 5, 3, 1);
	Parser::ParseResult r2 = parser2.parse("01234567.777abc0");

	BOOST_CHECK_EQUAL ('0',           at_c<0>(r2));
	BOOST_CHECK_EQUAL (1,             at_c<1>(r2));
	BOOST_CHECK_EQUAL (2,             at_c<2>(r2));
	BOOST_CHECK_EQUAL (3L,            at_c<3>(r2));
	BOOST_CHECK_EQUAL ((long long)4L, at_c<4>(r2));
	BOOST_CHECK_EQUAL (5.0f,          at_c<5>(r2));
	BOOST_CHECK_EQUAL ((double)6.0,   at_c<6>(r2));

	BOOST_CHECK_CLOSE ((long double)7.777, at_c<7>(r2), 0.000001);

	BOOST_CHECK_EQUAL ("abc", at_c<8>(r2));
	BOOST_CHECK_EQUAL (false, at_c<9>(r2));
}

BOOST_AUTO_TEST_CASE(parse_error)
{
	cpp::FixedColumnsParser<int, int> parser (2, 2);
	bool ok = false;
	try
	{
		parser.parse ("11ab");
	}
	catch (cpp::ParserException& e)
	{
		ok = true;
		BOOST_CHECK_EQUAL (1, e.err_column);
	}
	catch (...) {}
	if (! ok) BOOST_FAIL ("It was supposed to throw a ParserException exception.");
}

BOOST_AUTO_TEST_CASE (parse_stream_test)
{
	// Create test file.
	const char* file_name = "FixedColumnsParser_test_file.txt";
	ofstream out (file_name);
	out << "gato01\npato02\nsapo03";
	out.close ();

	cpp::FixedColumnsParser<string, int> parser (4, 2);
	ifstream in (file_name);
	cpp::FixedColumnsParser<string, int>::ParseStreamResult r = parser.parse (in);
	in.close ();

	BOOST_CHECK_EQUAL ((unsigned)3, r.size ()     );
	BOOST_CHECK_EQUAL ("gato",      at_c<0> (r[0]));
	BOOST_CHECK_EQUAL (1,           at_c<1> (r[0]));
	BOOST_CHECK_EQUAL ("pato",      at_c<0> (r[1]));
	BOOST_CHECK_EQUAL (2,           at_c<1> (r[1]));
	BOOST_CHECK_EQUAL ("sapo",      at_c<0> (r[2]));
	BOOST_CHECK_EQUAL (3,           at_c<1> (r[2]));
}

BOOST_AUTO_TEST_CASE (parse_file_error_test)
{
	cpp::FixedColumnsParser<string, int> parser (4, 2);

	// Create test file.
	const char* file_name = "FixedColumnsParser_test_file.txt";
	ofstream out (file_name);
	out << "gato01\nato02\nsapo03";
	out.close ();

	bool ok = false;
	try
	{
		parser.parse_file (file_name);
	}
	catch (cpp::ParserException& e)
	{
		ok = true;
		BOOST_CHECK_EQUAL (1, e.err_line);
		BOOST_CHECK_EQUAL ("The line 'ato02' was supposed to have 6 chars but it has 5 instead.", e.err_message);
	}
	catch (...) {}
	if (! ok) BOOST_FAIL ("It was supposed to throw a ParserException exception.");
}

BOOST_AUTO_TEST_CASE (parse_file_test)
{
	// Create test file.
	const char* file_name = "FixedColumnsParser_test_file.txt";
	ofstream out (file_name);
	out << "gato01\npato02\nsapo03";
	out.close ();

	cpp::FixedColumnsParser<string, int> parser (4, 2);
	cpp::FixedColumnsParser<string, int>::ParseStreamResult r = parser.parse_file (file_name);

	BOOST_CHECK_EQUAL ((unsigned)3, r.size ()     );
	BOOST_CHECK_EQUAL ("gato",      at_c<0> (r[0]));
	BOOST_CHECK_EQUAL (1,           at_c<1> (r[0]));
	BOOST_CHECK_EQUAL ("pato",      at_c<0> (r[1]));
	BOOST_CHECK_EQUAL (2,           at_c<1> (r[1]));
	BOOST_CHECK_EQUAL ("sapo",      at_c<0> (r[2]));
	BOOST_CHECK_EQUAL (3,           at_c<1> (r[2]));
}

BOOST_AUTO_TEST_CASE (parse_12_args_test)
{
	typedef cpp::FixedColumnsParser<int, string, string, string, string, string, string, string, string, string, string, string> PropayParser;
	PropayParser parser (5, 48, 41, 6, 23, 23, 23, 5, 9, 10, 20, 4);
	PropayParser::ParseResult r = parser.parse (line);
	BOOST_CHECK_EQUAL (15213,                                              at_c<0> (r));
	BOOST_CHECK_EQUAL ("MARCOS DA SILVA BRASILEIRO                      ", at_c<1> (r));
	BOOST_CHECK_EQUAL ("RUA RUA RUA RUA RUA RU                   ",        at_c<2> (r));
	BOOST_CHECK_EQUAL ("765   ",                                           at_c<3> (r));
	BOOST_CHECK_EQUAL ("APTO 23                ",                          at_c<4> (r));
	BOOST_CHECK_EQUAL ("POMPEIA                ",                          at_c<5> (r));
	BOOST_CHECK_EQUAL ("SAO PAULO              ",                          at_c<6> (r));
	BOOST_CHECK_EQUAL ("SP   ",                                            at_c<7> (r));
	BOOST_CHECK_EQUAL ("05617000 ",                                        at_c<8> (r));
	BOOST_CHECK_EQUAL ("          ",									   at_c<9> (r));
}

BOOST_AUTO_TEST_CASE (parse_trim_test)
{
	typedef cpp::FixedColumnsParser<int, string, string, string, string, string, string, string, string, string, string, string> PropayParser;
	PropayParser parser (5, 48, 41, 6, 23, 23, 23, 5, 9, 10, 20, 4);
	parser.trim_data = true;

	PropayParser::ParseResult r = parser.parse (line);
	BOOST_CHECK_EQUAL (15213,                        at_c<0> (r));
	BOOST_CHECK_EQUAL ("MARCOS DA SILVA BRASILEIRO", at_c<1> (r));
	BOOST_CHECK_EQUAL ("RUA RUA RUA RUA RUA RU",     at_c<2> (r));
	BOOST_CHECK_EQUAL ("765",                        at_c<3> (r));
	BOOST_CHECK_EQUAL ("APTO 23",                    at_c<4> (r));
	BOOST_CHECK_EQUAL ("POMPEIA",                    at_c<5> (r));
	BOOST_CHECK_EQUAL ("SAO PAULO",                  at_c<6> (r));
	BOOST_CHECK_EQUAL ("SP",                         at_c<7> (r));
	BOOST_CHECK_EQUAL ("05617000",                   at_c<8> (r));
	BOOST_CHECK_EQUAL ("",							 at_c<9> (r));
}

BOOST_AUTO_TEST_CASE (parse_pad_test)
{
	string line2 = "15213MARCOS DA SILVA BRASILEIRO                      RUA RUA RUA RUA RUA RU                   765   APTO 23                POMPEIA                SAO PAULO              SP   05617000";
	typedef cpp::FixedColumnsParser<int, string, string, string, string, string, string, string, string, string, string, string> PropayParser;
	PropayParser parser (5, 48, 41, 6, 23, 23, 23, 5, 9, 10, 20, 4);
	parser.trim_data = true;

	PropayParser::ParseResult r = parser.parse (line2, true);
	BOOST_CHECK_EQUAL (15213,                        at_c<0> (r));
	BOOST_CHECK_EQUAL ("MARCOS DA SILVA BRASILEIRO", at_c<1> (r));
	BOOST_CHECK_EQUAL ("RUA RUA RUA RUA RUA RU",     at_c<2> (r));
	BOOST_CHECK_EQUAL ("765",                        at_c<3> (r));
	BOOST_CHECK_EQUAL ("APTO 23",                    at_c<4> (r));
	BOOST_CHECK_EQUAL ("POMPEIA",                    at_c<5> (r));
	BOOST_CHECK_EQUAL ("SAO PAULO",                  at_c<6> (r));
	BOOST_CHECK_EQUAL ("SP",                         at_c<7> (r));
	BOOST_CHECK_EQUAL ("05617000",                   at_c<8> (r));
	BOOST_CHECK_EQUAL ("",							 at_c<9> (r));
}

BOOST_AUTO_TEST_CASE (performance_trim_test)
{
	typedef cpp::FixedColumnsParser<int, string, string, string, string, string, string, string, string, string, string, string> PropayParser;
	PropayParser parser (5, 48, 41, 6, 23, 23, 23, 5, 9, 10, 20, 4);
	parser.trim_data = true;

	for (int i = 0; i < 10000; i++)
	{
		PropayParser::ParseResult r = parser.parse (line);
	}
}

BOOST_AUTO_TEST_CASE (performance_pad_test)
{
	string line2 = "15213MARCOS DA SILVA BRASILEIRO                      RUA RUA RUA RUA RUA RU                   765   APTO 23                POMPEIA                SAO PAULO              SP   05617000";
	typedef cpp::FixedColumnsParser<int, string, string, string, string, string, string, string, string, string, string, string> PropayParser;
	PropayParser parser (5, 48, 41, 6, 23, 23, 23, 5, 9, 10, 20, 4);
	parser.trim_data = true;

	for (int i = 0; i < 10000; i++)
	{
		PropayParser::ParseResult r = parser.parse (line2, true);
	}
}

BOOST_AUTO_TEST_SUITE_END()
