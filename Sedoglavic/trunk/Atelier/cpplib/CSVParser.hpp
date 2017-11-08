// $Id$

#ifndef CSVPARSER_HPP_INCLUDED
#define CSVPARSER_HPP_INCLUDED

#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/regex.hpp>

#include "validation.hpp"
#include "string_util.h"
#include "log.h"

namespace pensar_digital
{
    namespace cpplib
    {
        namespace fs = boost::filesystem;

        /// Trimmer transformer trims the passed argument.
        template<class String = std::string>
        struct Trimmer
        {
            void apply (String& s) const
            {
                boost::trim (s);
            }
        };

        /// NoValidation always returns true for is_ok.
        template<typename T>
        struct NoValidation
        {
            bool is_ok (T value) const
            {
                return true;
            }
        };

        /// Do nothing while getting the values.
        /// Use a functor like this to collect information and avoid to loop through values more than once.
        /// \param value The raw string without transformation or validation.
        template<class String = std::string>
        struct DoNothing
        {
            void operator() (unsigned column, unsigned line, const String& value) {;}
        };

        template<class String = std::string>
        class CSVParser
        {
            typedef typename String::value_type CharT;
            typedef std::vector<String> Row;
            std::vector<Row> data;

            /// Number of lines to be skipped from the beginning of the file.
            unsigned skip_lines;

            /// Separator Char.
            CharT separator;

            /// Delimiter Char.
            CharT delimiter;

            /// Regular expression to parse the line.
            boost::regex re;

            /// Number of columns.
            /// If not provided as a constructor param it will be deduced by the number of
            /// separator chars in the first line of data.
            unsigned num_columns;

            /// Line that has the columns names.
            /// Default value = NO_TITLE_LINE.
            unsigned title_line;

            /// Title line flag. True => has title line, false otherwise.
            bool has_title_line;

            /// Maps columns names to columns numbers.
            /// Key = name, value = column number.
            std::map<String, unsigned> col_map;

            String build_regex (unsigned num_columns)
            {
                assert(num_columns > 0);

                String sregex = "^";
                while (--num_columns)
                {
                    sregex += "([^\t]*)\t{1}";
                }
                sregex += "([^\t]*)$";
                //cpplog << "sregex = " << sregex << std::endl;
                return sregex;
            }

            unsigned calculate_num_columns (const String& s)
            {
                return count(s.begin (), s.end (), separator) + 1;
            }

            public:

            /// Default value for title_line. No title line.
            static const unsigned NO_TITLE_LINE = (unsigned)-1;

            /// Default value for delimiter char. No delimiter.
            static const CharT NO_DELIMITER = -1;

            /// Defines which line contains the column names.
            /// Default value is NO_TITLE_LINE.
            /// First line is line 0.
            void set_title_line (unsigned line)
            {
                if (line != NO_TITLE_LINE)
                {
                    title_line = line;
                    has_title_line = true;
                }
                else
                    has_title_line = false;

                //cpplog << "has_title_line = " << has_title_line << std::endl;
            }

            /// Constructor.
            /// \param separator_char Char to be used as columns separator.
            /// \param num_lines_to_skip Lines to skip from the beginning. Default = 0.
            /// \param columns Number of columns. If not provided as a constructor param it will be deduced by the number of separator chars in the first line of data.
            CSVParser (CharT separator_char = '\t', CharT delimiter_char = NO_DELIMITER, unsigned columns = 0, unsigned num_lines_to_skip = 0) :
            data           (std::vector<Row>()           ),
            skip_lines     (num_lines_to_skip            ),
            separator      (separator_char               ),
            delimiter      (delimiter_char               ),
            re             (""                           ),
            num_columns    (columns                      ),
            title_line     (NO_TITLE_LINE                ),
            has_title_line (false                        ),
            col_map        (std::map<String, unsigned> ())
            {
                if (num_columns != 0)
                {
                    re.assign (build_regex (num_columns));
                }
            }

            /// Parses the given stream that is supposed to contain CSV data.
            /// \param in the stream to be parsed.
            template<typename Function = DoNothing<String>>
            void parse (const String& s, unsigned line_number, Function f = DoNothing<String>())
            {
                if (num_columns == 0)
                {
                    num_columns = calculate_num_columns (s);
                    re.assign (build_regex (num_columns));
                }

                min_check<unsigned> (num_columns, 0, USE_EXCEPTIONS);

                Row row;
                boost::smatch res;
                //LOG (s);
                if (boost::regex_match (s, res, re))
                {
                    //LOG ("matched");
                    for (unsigned col = 0; col < num_columns; ++col)
                    {
                        unsigned j = col + 1;
                        //LOG(res[j]);
                        row.push_back (res[j]);

                        /// In get line starts with zero. For file line number, it starts with 1. line_number should be greater than 0 here.
                        unsigned line = line_number - 1;

                        /// Calls functor passed by user.
                        f (col, line, res[j]);

                        //cpplog << "line_number = " << line_number << "title_line = " << title_line << std::endl;


                        if (has_title_line && line == title_line)
                        {
                            col_map[res[j]] = col;
                            //cpplog << "col_map[" << res[j] << "] = " << col << std::endl;
                        }

                        //cpplog << "row.size = " << row.size () << std::endl;
                    }
                    data.push_back (row);
                    //cpplog << "data.size = " << data.size () << std::endl;
                }
                else
                {
                    String trimmed = s;
                    boost::trim (trimmed);
                    if (trimmed.size () > 0)
                    {
                        std::stringstream ss;
                        ss << __FILE__ << "\t" << __LINE__ << "\t Linha mal formatada (" << line_number << "): " << s << std::endl;
                        std::cerr << ss.str ();
                        //cpplog << ss.str ();
                        std::logic_error e (ss.str ());
                        throw e;
                    }
                }
            }

            /// Parses the given stream that is supposed to contain CSV data.
            /// \param in the stream to be parsed.
            template<typename Function = DoNothing<String>>
            void parse_stream (std::istream& in, Function f = DoNothing<String>())
            {
                String line;
                unsigned line_number = 0;
                while (! in.eof ())
                {
                    getline (in, line);
                    ++line_number;
                    if (line_number > skip_lines)
                    {
                        parse (line, line_number, f);
                    }
                }
            }

            /// Parses the given CSV file.
            /// \param file the complete path for the file or the file name (default dir is platform dependent).
            /// \throws std::exception if file cannot be openned.
            template<typename Function = DoNothing<String>>
            void parse (const fs::path& file, Function f = DoNothing<String>())
            {
                fs::ifstream in(file);
                if (in)
                    parse_stream (in, f);
                else
                {
                    std::stringstream ss;
                    ss << __FILE__ << "\t" << __LINE__ << "\t Nao foi possivel abrir " << file.file_string () << std::endl;
                    std::cerr << ss.str ();
                    std::logic_error e(ss.str ());
                    throw e;
                }
            }

            /// Gets the number of parsed columns.
            /// Call this only after calling parse. If called before it will return 0.
            /// \return unsigned the number of parsed columns.
            unsigned get_num_columns () { return num_columns; }

            /// Gets the number of parsed lines with actual data. It does not count skipped lines.
            /// \return unsigned the number of non-skipped lines.
            unsigned get_num_lines   () { return data.size (); }

            /// Gets the string value, applies transformation then validation and returns casted type.
            /// \param column the column to index the data. First column is 0.
            /// \param line the line to index the data. First line is 0.
            /// \param default_value the string to be used in the abscense of data provided by the file. The transformer will not be applied, the validation will.
            /// \param t the transformation to be applied in the data string with t.apply(String).
            /// \param v the validation to be applied in the transforemd and casted data with v.is_ok (T)
            /// \throws std::logic_error if column or line are invalid or if validation fails.
            /// \throws boost::bad_cast_exception if String value cannot be static casted to T.
            /// \throws std::invalid_argument exception if column or line are not in range [0, num_columns[ and [0, num_lines[.
            template <typename T, class Transformer = Trimmer<String>, typename Validator = NoValidation<T>>
            T get (unsigned column, unsigned line, bool use_default = true, const String& default_value = "0", const Transformer& t = Trimmer<String>(), const Validator& v = NoValidation<T>())
            {
                //assert(range_check<unsigned> (column, 0, get_num_columns () - 1));
                //cpplog << "column = " << column << " line = " << line << " num_lines = " << get_num_lines () << std::endl;
                //assert(range_check<unsigned> (line  , 0, get_num_lines   () - 1));

                range_check<unsigned> (column, 0, get_num_columns () - 1, "column", cpplib::USE_EXCEPTIONS);
                range_check<unsigned> (line  , 0, get_num_lines   () - 1, "line"  , cpplib::USE_EXCEPTIONS);

                String& s = data[line][column];
                if (use_default && s.size () == 0)
                    s = default_value;
                //cpplog << "s = " << s << std::endl;

                if (delimiter != NO_DELIMITER)
                    remove_delimiters (delimiter, s);

                t.apply (s);
                T value = boost::lexical_cast<T> (s);
                if (! v.is_ok (value))
                    throw std::logic_error ("Validation failed.\n");
                return value;
            }

            template <typename T, class Transformer = Trimmer<String>, typename Validator = NoValidation<T>>
            T get (String column_name, unsigned line, bool use_default = true, const String& default_value = "0", const Transformer& t = Trimmer<String>(), const Validator& v = NoValidation<T>())
            {
                return get<T> (col_map[column_name], line, use_default, default_value, t, v);
            }
        };
    }   // namespace cpplib
}       // namespace pensar_digital

#endif // CSVPARSER_HPP_INCLUDED
