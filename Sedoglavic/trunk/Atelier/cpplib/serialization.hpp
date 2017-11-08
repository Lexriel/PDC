#ifndef SERIALIZATION_HPP_INCLUDED
#define SERIALIZATION_HPP_INCLUDED

#include <iostream>
#include <sstream>
#include <string>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/xml_oarchive.hpp> // Archive for writing XML
#include <boost/archive/xml_iarchive.hpp> // Archive for reading XML
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/slist.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/scoped_ptr.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/void_cast.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/serialization/wrapper.hpp>
#include <boost/serialization/traits.hpp>
#include <boost/serialization/hash_map.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/archive/archive_exception.hpp>

namespace pensar_digital
{
    namespace cpplib
    {
        namespace serialization
        {
            namespace ser = boost::serialization;

            template <typename T, typename OutputArchiveType = boost::archive::text_oarchive>
            std::string to_string (const T& value)
            {
               std::stringstream ss (std::stringstream::in | std::stringstream::out);
               OutputArchiveType oa (ss);
               oa << ser::make_nvp("value", value);

               return ss.str ();
            }

            template <typename T, typename InputArchiveType = boost::archive::text_iarchive>
            T from_string (const std::string& s)
            {
               std::stringstream ss (std::stringstream::in | std::stringstream::out);
               ss << s;
               InputArchiveType ia (ss);
               T value;
               ia >> ser::make_nvp("value", value);
               return value;
            }

            template <typename T>
            std::string to_xml (const T& value)
            {
                return to_string<boost::archive::xml_oarchive> (value);
            }

            template <typename T>
            T from_xml (const std::string& xml_string)
            {
                return from_string<boost::archive::xml_iarchive> (xml_string);
            }
        }
    }
}


#endif // SERIALIZATION_HPP_INCLUDED
