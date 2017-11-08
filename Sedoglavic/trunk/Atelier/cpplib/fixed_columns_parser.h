// $Id: fixed_columns_parser.h 40 2010-07-16 22:04:49Z mgpensar $

#ifndef fixed_columns_parserH
#define fixed_columns_parserH

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#define FUSION_MAX_VECTOR_SIZE 20
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/include/vector_fwd.hpp>

#include "boost/lexical_cast.hpp"
#include "boost/algorithm/string.hpp"
#include "string_util.h"

namespace pensar_digital
{
    namespace cpplib
    {
        struct ParserException
        {
            int err_line;
            int err_column;
            std::string err_message;
        };

        const int MAX_SIZE = 12;

        ///////////////////////////////////////////////////////////////////////////
        /// FixedColumnsParser parses text files with fixed sized columns.
        ///
        /// When compilers support variadic templates the interface will use that.
        ///
        template <typename T0 = int, typename T1 = int, typename T2 = int,
                  typename T3 = int, typename T4 = int, typename T5 = int,
                  typename T6 = int, typename T7 = int, typename T8 = int,
                  typename T9 = int, typename T10 = int, typename T11 = int>
        class FixedColumnsParser
        {
            int sizes[MAX_SIZE];
            public:
            bool trim_data;
            FixedColumnsParser (int size0  = 0, int size1 = 0, int size2 = 0, int size3 = 0, int size4 = 0,
                         int size5  = 0, int size6 = 0, int size7 = 0, int size8 = 0, int size9 = 0,
                         int size10 = 0, int size11 = 0)
            {
                trim_data = false;
                sizes[0] = size0;
                sizes[1] = size1;
                sizes[2] = size2;
                sizes[3] = size3;
                sizes[4] = size4;
                sizes[5] = size5;
                sizes[6] = size6;
                sizes[7] = size7;
                sizes[8] = size8;
                sizes[9] = size9;
                sizes[10] = size10;
                sizes[11] = size11;
            };


          typedef boost::fusion::vector<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11> ParseResult;
          typedef std::vector<ParseResult> ParseStreamResult;

          ParseResult parse (const std::string& str, bool bpad = false)
          {
            // Verifies if string size is correct.
            int expected_size = 0;
            for (int i = 0; i < MAX_SIZE; i++)
            {
                expected_size += sizes[i];
            }
            int size = str.length ();

            // Cast used to save a string copy. The remaining code will not change the string str.
            //std::string& s = (std::string)str;
            std::string s = str;

            if (size != expected_size)
            {
                if (bpad)
                {
                    pad (s, ' ', expected_size);
                }
                else
                {
                    ParserException e;
                    e.err_line    = -1;
                    e.err_column  = -1;
                    e.err_message = "The line '" + s + "' was supposed to have "
                               + boost::lexical_cast<std::string>(expected_size) + " chars but it has "
                               + boost::lexical_cast<std::string>(s.length ()) + " instead.";
                    throw (e);
                }
            }

            int offset = 0;
            int passed = -1;
            T0 v0; T1 v1; T2 v2; T3 v3; T4 v4; T5 v5; T6 v6; T7 v7; T8 v8; T9 v9; T10 v10; T11 v11;

            std::string str0 = s.substr (0, sizes[0]);
            try
            {
                if (trim_data) boost::trim (str0);
                v0 = boost::lexical_cast<T0> (str0);
                ++passed;
                if (sizes[1])
                {
                    std::string str1 = s.substr (offset += sizes[0], sizes[1]);
                    if (trim_data) boost::trim (str1);
                    v1 = boost::lexical_cast<T1> (str1);
                    ++passed;
                    if (sizes[2])
                    {
                        std::string str2 = s.substr (offset += sizes[1], sizes[2]);
                        if (trim_data) boost::trim (str2);
                        v2 = boost::lexical_cast<T2> (str2);
                        ++passed;
                        if (sizes[3])
                        {
                            std::string str3 = s.substr (offset += sizes[2], sizes[3]);
                            if (trim_data) boost::trim (str3);
                            v3 = boost::lexical_cast<T3> (str3);
                            ++passed;
                            if (sizes[4])
                            {
                                std::string str4 = s.substr (offset += sizes[3], sizes[4]);
                                if (trim_data) boost::trim (str4);
                                v4 = boost::lexical_cast<T4> (str4);
                                ++passed;
                                if (sizes[5])
                                {
                                    std::string str5 = s.substr (offset += sizes[4], sizes[5]);
                                    if (trim_data) boost::trim (str5);
                                    v5 = boost::lexical_cast<T5> (str5);
                                    ++passed;
                                    if (sizes[6])
                                    {
                                        std::string str6 = s.substr (offset += sizes[5], sizes[6]);
                                        if (trim_data) boost::trim (str6);
                                        v6 = boost::lexical_cast<T6> (str6);
                                        ++passed;
                                        if (sizes[7])
                                        {
                                            std::string str7 = s.substr (offset += sizes[6], sizes[7]);
                                            if (trim_data) boost::trim (str7);
                                            v7 = boost::lexical_cast<T7> (str7);
                                            ++passed;
                                            if (sizes[8])
                                            {
                                                std::string str8 = s.substr (offset += sizes[7], sizes[8]);
                                                if (trim_data) boost::trim (str8);
                                                v8 = boost::lexical_cast<T8> (str8);
                                                ++passed;
                                                if (sizes[9])
                                                {
                                                    std::string str9 = s.substr (offset += sizes[8], sizes[9]);
                                                    if (trim_data) boost::trim (str9);
                                                    v9 = boost::lexical_cast<T9> (str9);
                                                    ++passed;
                                                    if (sizes[10])
                                                    {
                                                        std::string str10 = s.substr (offset += sizes[9], sizes[10]);
                                                        if (trim_data) boost::trim (str10);
                                                        v10 = boost::lexical_cast<T10> (str10);
                                                        ++passed;
                                                        if (sizes[11])
                                                        {
                                                            std::string str11 = s.substr (offset += sizes[10], sizes[11]);
                                                            if (trim_data) boost::trim (str11);
                                                            v11 = boost::lexical_cast<T11> (str11);
                                                            ++passed;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            catch (boost::bad_lexical_cast& e)
            {
                ParserException pe;
                pe.err_line = 0;
                pe.err_column = passed + 1;
                pe.err_message = "Column " + boost::lexical_cast<std::string> (pe.err_column) + " has an invalid value.";
                throw pe;
            }

            ParseResult r (v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11);
            return r;
          };

          ParseStreamResult parse (std::istream& in, int ignore_first_lines = 0, bool pad = false)
          {
            std::string line;
            ParseStreamResult r;
            int line_number = 0;
            const char eol = '\n';
            try
            {
                while (! in.eof() && ignore_first_lines--)
                    getline (in, line, eol);
                while (! in.eof())
                {
                    getline (in, line, eol);
                    if (line.size () > 0)
                    {
                        r.push_back (parse (line, pad));
                        ++line_number;
                    }
                }
            }
            catch (ParserException& e)
            {
                e.err_line = line_number;
                throw (e);
            }
            return r;
          };

          ParseStreamResult parse_file (const char* file_full_path, int ignore_first_lines = 0, bool pad = false)
          {
            std::ifstream in (file_full_path);
            ParseStreamResult r;
            try
            {
                if (in)
                    r = parse (in, ignore_first_lines, pad);
            }
            catch (ParserException& e)
            {
                if (in) in.close ();
                throw e;
            }
            catch (...)
            {
                if (in) in.close ();
                throw ("Unknown exception.");
            }
            return r;
          };
        };
    }   // namespace cpplib
}       // namespace pensar_digital
#endif
