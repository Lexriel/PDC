//---------------------------------------------------------------------------
// $Id: filesystem_util.h 59 2011-01-02 20:11:16Z mgpensar $

#ifndef filesystem_utilH
#define filesystem_utilH

#include <string>
#include <vector>
#include <memory>
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/cerrno.hpp>
#include <boost/config.hpp>
#include <boost/regex.hpp>

namespace fs = boost::filesystem;

namespace pensar_digital
{
    /// cpplib is the root namespace for all cpplib code.
    namespace cpplib
    {
        using boost::system::error_code;
        using boost::system::system_category;
        using boost::system::system_error;

        extern const bool INCLUDE_DIRS;
        extern const bool DO_NOT_INCLUDE_DIRS;
        extern const bool RECURSIVE;
        extern const bool NO_RECURSION;
        extern const std::string NO_FILTER;

        /// An auto pointer for a vector of paths.
        /// Use it as a regular pointer. It will be dealocated automatically when leaving scope.
        typedef std::vector<fs::path> PathContainer;
        typedef std::unique_ptr<PathContainer> PathVectorPtr;

        /// Creates a file as passed by the path argument.
        /// If path includes dirs that do not exist these are created accordingly.
        template <typename Streamable>
        void create_file (const fs::path& path, const Streamable& contents)
        {
            if (! fs::exists (path.parent_path ()))
                fs::create_directories (path.parent_path ());
            fs::ofstream f (path);
            if (!f)
              throw fs::filesystem_error ("filesystem_util create_file", path, error_code (errno, system_category ()));
            //if (!contents.empty ()) f << contents;
            f << contents;
        }

        /// It gets files and/or directories in the specified path.
        /// The parameter pattern uses regular expressions according to http://www.boost.org/doc/libs/1_38_0/libs/regex/doc/html/boost_regex/syntax/perl_syntax.html.
        /// \param dir the path where to start the search.
        /// \param pattern regular expression used to filter the results.
        /// \param include_dirs if INCLUDE_DIRS then includes the directories in the result.
        /// \result an auto_ptr to a vector of paths.
        template <class DirectoryIterator>
        PathVectorPtr get_files (fs::path dir, std::string pattern, bool include_dirs)
        {
            PathVectorPtr files(new std::vector<fs::path> ());
            if (!exists (dir)) return files;
            DirectoryIterator end; // default construction yields past-the-end
            bool use_regex = pattern != "";
            boost::regex re(pattern);
            for (DirectoryIterator i (dir); i != end; ++i)
            {
                bool is_dir = is_directory (i->status());
                if (include_dirs || !is_dir)
                {
                    if (!use_regex || boost::regex_match (i->path ().string (), re))
                    files->push_back (i->path ());
                }
            }
            return files;
        }

        /// It gets files and/or directories in the specified path.
        /// The parameter pattern uses regular expressions according to http://www.boost.org/doc/libs/1_38_0/libs/regex/doc/html/boost_regex/syntax/perl_syntax.html.
        /// \param dir the path where to start the search.
        /// \param pattern regular expression used to filter the results.
        /// \param include_dirs if INCLUDE_DIRS then includes the directories in the result.
        /// \param recursive if RECURSIVE then recursively reads sub-directories.
        /// \result an auto_ptr to a vector of paths.
        inline PathVectorPtr get_files (fs::path dir, std::string pattern = NO_FILTER, bool include_dirs = DO_NOT_INCLUDE_DIRS
                                                                                     , bool recursive    = NO_RECURSION)
        {
            return recursive ? get_files<fs::basic_recursive_directory_iterator<fs::path> > (dir, pattern, include_dirs)
                             : get_files<fs::directory_iterator >                           (dir, pattern, include_dirs);
        }

        template<typename T>
        void copy (const std::basic_string<T>& src, const std::basic_string<T>& dst)
        {
            fs::path _src = complete (fs::path (src , fs::native));
            fs::path _dst = complete (fs::path (dst , fs::native));
            fs::copy_file (src, dst);
        }
    }   // namespace cpplib
}       // namespace pensar_digital
/// \example filesystem_util_example.cpp
/// filesystem_util usage examples.
#endif
