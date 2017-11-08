#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>


#include <boost/test/unit_test.hpp>

#include <filesystem_util.h>
#include <io_util.h>
#include "my_boost.hpp"

using namespace std;
using namespace boost::unit_test_framework;
using namespace cpplib;

const fs::path test_base_path = "dir_util_test_dir";

// This test suite fixture creates the directory tree below needed for the tests.
// dir_util_test_dir
//       |
//       +- file1
//       |
//       +- file2
//       |
//       +- dir1
//       |    |
//       |    +- file3
//       |
//       +- dir2
//       |    |
//       |    +- file4
//       |
//       +- dir3
//       |
//       +- dir4
//            |
//            +- dir5
//                |
//                +- dir6
//                    |
//                    +- file5
struct F
{
    F() : d1(test_base_path / "dir1"),
          d2(test_base_path / "dir2"),
          d3(test_base_path / "dir3"),
          d4(test_base_path / "dir4"),
          d5(d4 / "dir5"),
          d6(d5 / "dir6"),
          p1(test_base_path / "file1"),
          p2(test_base_path / "file2"),
          p3(d1 / "file3"),
          p4(d2 / "file4"),
          p5(d6 / "file5")
    {
        if (fs::exists (test_base_path))
            fs::remove_all (test_base_path);
        create_file<string>  (p1, "");
        create_file<string>  (p2, "");
        create_file<string>  (p3, "");
        create_file<string>  (p4, "");
        create_file<string>  (p5, "");
        fs::create_directory (d3);
    }

    ~F()
    {
        //fs::remove_all (test_base_path);
    }

    fs::path d1;
    fs::path d2;
    fs::path d3;
    fs::path d4;
    fs::path d5;
    fs::path d6;
    fs::path p1;
    fs::path p2;
    fs::path p3;
    fs::path p4;
    fs::path p5;
};

BOOST_FIXTURE_TEST_SUITE(dir_util_suite, F)

BOOST_AUTO_TEST_CASE(get_files_test0)
{
    vector<fs::path> expected;
    expected.push_back (p1);
    expected.push_back (p2);
    sort (expected.begin (), expected.end ());
    auto_ptr<vector<fs::path> > files = get_files (test_base_path);
    sort (files->begin (), files->end ());
    CHECK_EQUAL_COLLECTIONS (expected, *files);

    // Tests the default parameters are the ones expected.
    auto_ptr<vector<fs::path> > files2 = get_files (test_base_path, NO_FILTER, DO_NOT_INCLUDE_DIRS, NO_RECURSION);
    sort (files2->begin (), files2->end ());
    CHECK_EQUAL_COLLECTIONS (expected, *files2);
}

BOOST_AUTO_TEST_CASE(get_files_test1)
{
    vector<fs::path> expected;
    expected.push_back (p1);
    expected.push_back (p2);
    expected.push_back (p3);
    expected.push_back (p4);
    expected.push_back (p5);
    sort (expected.begin (), expected.end ());
    auto_ptr<vector<fs::path> > files = get_files (test_base_path, NO_FILTER, DO_NOT_INCLUDE_DIRS, RECURSIVE);
    sort (files->begin (), files->end ());
    CHECK_EQUAL_COLLECTIONS (expected, *files);
}

BOOST_AUTO_TEST_CASE(get_files_test2)
{
    vector<fs::path> expected;
    expected.push_back (p3);
    auto_ptr<vector<fs::path> > files = get_files (test_base_path, ".*3.*", DO_NOT_INCLUDE_DIRS, RECURSIVE);
    CHECK_EQUAL_COLLECTIONS (expected, *files);
}

BOOST_AUTO_TEST_CASE(get_files_test3)
{
    vector<fs::path> expected;
    expected.push_back (p3);
    expected.push_back (d3);
    sort (expected.begin (), expected.end ());
    auto_ptr<vector<fs::path> > files = get_files (test_base_path, ".*3.*", INCLUDE_DIRS, RECURSIVE);
    sort (files->begin (), files->end ());
    CHECK_EQUAL_COLLECTIONS (expected, *files);
}

BOOST_AUTO_TEST_CASE(get_files_test4)
{
    vector<fs::path> expected;
    expected.push_back (p1);
    expected.push_back (p2);
    expected.push_back (p3);
    expected.push_back (p4);
    expected.push_back (p5);
    expected.push_back (d1);
    expected.push_back (d2);
    expected.push_back (d3);
    expected.push_back (d4);
    expected.push_back (d5);
    expected.push_back (d6);
    sort (expected.begin (), expected.end ());
    auto_ptr<vector<fs::path> > files = get_files (test_base_path, NO_FILTER, INCLUDE_DIRS, RECURSIVE);
    sort (files->begin (), files->end ());
    CHECK_EQUAL_COLLECTIONS (expected, *files);
}

BOOST_AUTO_TEST_SUITE_END ()
