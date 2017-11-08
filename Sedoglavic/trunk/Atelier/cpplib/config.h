// $Id: config.h 65 2011-08-03 04:36:31Z mgpensar $

#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#ifdef VISUAL_STUDIO
#include "stdafx.h"
#endif
#include <cstddef> // NULL
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include <boost/archive/tmpdir.hpp>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <boost/filesystem/fstream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include "serialization.hpp"
#include <boost/serialization/nvp.hpp>

namespace fs = boost::filesystem;

namespace pensar_digital
{
    namespace cpplib
    {
        namespace serial = boost::serialization;

        /// Manages a map of properties. Serializes to filesystem for persistence in a configuration file.
        /// Examples: \ref config_manager_test.cpp
        template <typename String = std::string, typename OutputArchiveType = boost::archive::text_oarchive, typename InputArchiveType = boost::archive::text_iarchive>
        class Config
        {
            public:

            /// Property is used to store the property value and auxiliary information like display_name.
            class Property
            {
                public:
                String value;
                String display_name;

                // Added this default constructor just for serialization. Do not use it.
                Property () {};
                Property (const String& value_, String display_name_ = ""): value(value_), display_name(display_name_) {}

                friend class boost::serialization::access;
                template<class Archive>
                void serialize(Archive & ar, const unsigned int version)
                {
                    ar & BOOST_SERIALIZATION_NVP(value);
                    ar & BOOST_SERIALIZATION_NVP(display_name);
                }
            };

            typedef boost::shared_ptr<Property> PropertyPtr;

            typedef std::map<String,  PropertyPtr> PropertiesMap;

            private:
            fs::path full_path;
            PropertiesMap cfg;

            public:
            Config<String, OutputArchiveType, InputArchiveType> (fs::path fullpath = "config.txt") : full_path (fullpath)
            {
                full_path = fs::system_complete (fullpath);
                load ();
            };

            void save ()
            {
                fs::ofstream ofs (full_path);
                OutputArchiveType oa (ofs);
                oa << BOOST_SERIALIZATION_NVP(cfg);
            }

            void load ()
            {
                if (fs::exists (full_path))
                {
                    fs::ifstream ifs (full_path);
                    InputArchiveType ia (ifs);
                    ia >> BOOST_SERIALIZATION_NVP(cfg);
                }
            }

            template <typename T>
            bool get (const String& key, T& out)
            {
                //boost::lexical_cast<T>(cfg[key]->value)
                bool ok = false;
                typename PropertiesMap::iterator i = cfg.find (key);
                if (i != cfg.end ())
                {
                    out = serialization::from_string<T, boost::archive::text_iarchive>(i->second->value);
                    ok = true;
                }
                return  ok;
            }

            template <typename T>
            void set (const String& key, const T& value, String display_name = "")
            {
                PropertyPtr pp (new Property (serialization::to_string<T, boost::archive::text_oarchive>(value), display_name));
                cfg[key] = pp;
            }
        };
    }   // namespace cpplib
}       // namespace pensar_digital


#endif