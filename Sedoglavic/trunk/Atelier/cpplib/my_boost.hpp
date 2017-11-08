#ifndef MY_BOOST_HPP_INCLUDED
#define MY_BOOST_HPP_INCLUDED

#define CHECK_EQUAL_COLLECTIONS(L, R)         \
  BOOST_CHECK_EQUAL_COLLECTIONS((L).begin (), (L).end (), (R).begin (), (R).end ())

#include <boost/foreach.hpp>
#define foreach         BOOST_FOREACH

#endif // MY_BOOST_HPP_INCLUDED
