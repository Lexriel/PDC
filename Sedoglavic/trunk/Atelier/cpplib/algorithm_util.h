#ifndef ALGORITHM_UTIL_H_INCLUDED
#define ALGORITHM_UTIL_H_INCLUDED

#include<map>
#include<string>

namespace pensar_digital
{
    namespace cpplib
    {
        template<
           typename T,
           typename Alloc,
           template<typename, typename> class Container,
           typename Predicate
        >
        Container<T, Alloc>& erase_if(Container<T, Alloc>& c, Predicate p)
        {
            c.erase (std::remove_if (c.begin (), c.end (), p), c.end ());
            return c;
        }

        template<
           typename Key,
           typename T,
           typename Compare,
           typename Alloc,
           template<typename, typename, typename, typename> class MapClass,
           typename Predicate
        >
        void erase_if(MapClass<Key, T, Compare, Alloc>& map, Predicate p)
        {
            typedef typename MapClass<Key, T, Compare, Alloc>::iterator iterator;
            for (iterator it = map.begin (); it != map.end (); ++it)
            {
                if (p (*it))
                    map.erase (it);
            }
        }

        template<typename In, typename Out, typename Pred>
        Out copy_if(In first, In last, Out res, Pred Pr)
        {
            while (first != last)
            {
              if (Pr(*first))
                *res++ = *first;
              ++first;
            }

            return res;
        }
    }   // namespace cpplib
}       // namespace pensar_digital
#endif // ALGORITHM_UTIL_H_INCLUDED
