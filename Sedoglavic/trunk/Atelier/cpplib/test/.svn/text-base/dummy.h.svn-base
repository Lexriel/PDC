#ifndef DUMMY_H
#define DUMMY_H

#include <string>
#include <vector>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>

namespace pensar_digital
{
    namespace cpplib
    {
        namespace test
        {
            class Dummy
            {
                private:
                std::string s;
                int i;
                std::vector<std::string> slist;

                friend class boost::serialization::access;
                template<typename Archive>
                void serialize(Archive& ar, const unsigned int version)
                {
                    ar & BOOST_SERIALIZATION_NVP(s);
                    ar & BOOST_SERIALIZATION_NVP(i);
                    ar & BOOST_SERIALIZATION_NVP(slist);
                }

                public:
                Dummy (std::string s_, int i_, const std::vector<std::string>& slist_): s(s_), i(i_), slist(slist_) {}
                Dummy () {};

                friend bool operator== (const Dummy& left, const Dummy& right);
            };

            extern bool operator== (const Dummy& left, const Dummy& right);
        }
    }
}

#endif // DUMMY_H
