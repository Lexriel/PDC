#include <boost/test/unit_test.hpp>

#include <string>
#include <sstream>
#include <boost\filesystem.hpp>

#include "CSVParser.hpp"

namespace pd = pensar_digital::cpplib;
namespace fs = boost::filesystem;

struct Fixture
{
    std::string      colname0;
    std::string      colname1;
    std::string      colname2;
    int              expected_c00;
    std::string      expected_c01;
    std::string      expected_c02;
    int              expected_c10;
    std::string      expected_c11;
    std::string      expected_c12;
    static const char* S;
    std::stringstream ss;

    Fixture () :
    colname0("col0"), colname1     ("col1"),     colname2     ("col2"),
    expected_c00 (0), expected_c01 ("svalue01"), expected_c02 ("svalue02"),
    expected_c10 (1), expected_c11 ("svalue11"), expected_c12 ("svalue12")
    {
        ss << colname0     << S << colname1     << S << colname2     << std::endl;
        ss << expected_c00 << S << expected_c01 << S << expected_c02 << std::endl;
        ss << expected_c10 << S << expected_c11 << S << expected_c12 << std::endl;
    }
};

const char* Fixture::S = "\t";

BOOST_FIXTURE_TEST_SUITE(CSVParser_suite, Fixture)

BOOST_AUTO_TEST_CASE(parse_test)
{
    using std::string;

    pd::CSVParser<> parser ('\t', pd::CSVParser<>::NO_DELIMITER, 3, 1);
    parser.parse_stream<> (ss);

    unsigned i = parser.get_num_columns ();
    unsigned j = parser.get_num_lines   ();

    BOOST_CHECK_EQUAL (3u, i);
    BOOST_CHECK_EQUAL (2u, j);
    BOOST_CHECK_EQUAL (expected_c00, parser.get<int   >(0,0));
    BOOST_CHECK_EQUAL (expected_c01, parser.get<string>(1,0));
    BOOST_CHECK_EQUAL (expected_c02, parser.get<string>(2,0));
    BOOST_CHECK_EQUAL (expected_c10, parser.get<int   >(0,1));
    BOOST_CHECK_EQUAL (expected_c11, parser.get<string>(1,1));
    BOOST_CHECK_EQUAL (expected_c12, parser.get<string>(2,1));
}

BOOST_AUTO_TEST_CASE(parse_test2)
{
    using std::string;

    pd::CSVParser<> parser;
    parser.parse_stream<> (ss);

    unsigned i = parser.get_num_columns ();
    unsigned j = parser.get_num_lines   ();

    BOOST_CHECK_EQUAL (3u, i);
    BOOST_CHECK_EQUAL (3u, j);
    BOOST_CHECK_EQUAL (expected_c00, parser.get<int   >(0,1));
    BOOST_CHECK_EQUAL (expected_c01, parser.get<string>(1,1));
    BOOST_CHECK_EQUAL (expected_c02, parser.get<string>(2,1));
    BOOST_CHECK_EQUAL (expected_c10, parser.get<int   >(0,2));
    BOOST_CHECK_EQUAL (expected_c11, parser.get<string>(1,2));
    BOOST_CHECK_EQUAL (expected_c12, parser.get<string>(2,2));
}

BOOST_AUTO_TEST_CASE(parse_col_names_test)
{
    using std::string;

    pd::CSVParser<> parser ('\t');
    parser.set_title_line (0);
    parser.parse_stream<> (ss);

    unsigned i = parser.get_num_columns ();
    unsigned j = parser.get_num_lines   ();

    BOOST_CHECK_EQUAL (3u, i);
    BOOST_CHECK_EQUAL (3u, j);
    BOOST_CHECK_EQUAL (colname0    , parser.get<string>(colname0, 0));
    BOOST_CHECK_EQUAL (colname1    , parser.get<string>(colname1, 0));
    BOOST_CHECK_EQUAL (colname2    , parser.get<string>(colname2, 0));
    BOOST_CHECK_EQUAL (expected_c00, parser.get<int   >(colname0, 1));
    BOOST_CHECK_EQUAL (expected_c01, parser.get<string>(colname1, 1));
    BOOST_CHECK_EQUAL (expected_c02, parser.get<string>(colname2, 1));
    BOOST_CHECK_EQUAL (expected_c10, parser.get<int   >(colname0, 2));
    BOOST_CHECK_EQUAL (expected_c11, parser.get<string>(colname1, 2));
    BOOST_CHECK_EQUAL (expected_c12, parser.get<string>(colname2, 2));

    BOOST_CHECK_EQUAL ((unsigned)expected_c00, parser.get<unsigned>(colname0, 1));
}

BOOST_AUTO_TEST_CASE(parse_test3)
{
    using std::string;

    pd::CSVParser<> parser ('\t', pd::CSVParser<>::NO_DELIMITER, 7 /* # of columns*/);
    parser.set_title_line (0);

    fs::path in ("..\\cpplib\\test\\data\\mso_4D.txt");

    parser.parse<> (in);
    unsigned i = parser.get_num_columns ();
    unsigned j = parser.get_num_lines   ();

    BOOST_CHECK_EQUAL (7u , i);
    BOOST_CHECK_EQUAL (341u, j);
    BOOST_CHECK_EQUAL (147u, parser.get<unsigned>(0, 340));
    std::string mso_name = "Way TV Belo Horizonte";
    BOOST_CHECK_EQUAL (mso_name, parser.get<string>(1, 340));
    BOOST_CHECK_EQUAL (mso_name, parser.get<string>("Operacao", 340));
}

BOOST_AUTO_TEST_CASE(parse_trimmer_test)
{
    using std::string;

    pd::CSVParser<> parser;
    std::stringstream ss;
    ss << " a " <<  '\t' << "   b" << '\t' << "c    ";
    parser.parse_stream<> (ss);
    unsigned i = parser.get_num_columns ();
    unsigned j = parser.get_num_lines   ();

    BOOST_CHECK_EQUAL (3u, i);
    BOOST_CHECK_EQUAL (1u, j);
    BOOST_CHECK_EQUAL ("a", parser.get<string>(0, 0));
    BOOST_CHECK_EQUAL ("b", parser.get<string>(1, 0));
    BOOST_CHECK_EQUAL ("c", parser.get<string>(2, 0));
}

BOOST_AUTO_TEST_CASE(parse_delimitado_test)
{
    using std::string;

    pd::CSVParser<> parser ('\t', '"');
    std::stringstream ss;
    ss << "\" a \"" <<  '\t' << "\"   b\"" << '\t' << "\"c    \"";
    parser.parse_stream<> (ss);
    unsigned i = parser.get_num_columns ();
    unsigned j = parser.get_num_lines   ();

    BOOST_CHECK_EQUAL (3u, i);
    BOOST_CHECK_EQUAL (1u, j);
    BOOST_CHECK_EQUAL ("a", parser.get<string>(0, 0));
    BOOST_CHECK_EQUAL ("b", parser.get<string>(1, 0));
    BOOST_CHECK_EQUAL ("c", parser.get<string>(2, 0));
}

BOOST_AUTO_TEST_SUITE_END ()
