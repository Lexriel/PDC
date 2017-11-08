#ifndef DISTANCE_HPP_INCLUDED
#define DISTANCE_HPP_INCLUDED

#include <string>
#include <set>
#include <vector>
#include <limits>

#include "error.hpp"
#include "log.h"

namespace pensar_digital
{
    namespace cpplib
    {
        namespace pd = pensar_digital::cpplib;

        /// Levenshtein Distance Algorithm
        // adapted from Anders Sewerin Johansen code.
        template<typename String = std::string>
        int distance (const String& source, const String& target)
        {
            //cpplog << "source = " << source << " " << "target = " << target << std::endl;
            //LOG_FLUSH
            // Step 1
            const int n = source.length ();
            const int m = target.length ();

            if (n == 0) return m;
            if (m == 0) return n;

            typedef std::vector< std::vector<int> > Tmatrix;

            Tmatrix matrix(n+1);

            // Size the vectors in the 2.nd dimension. Unfortunately C++ doesn't
            // allow for allocation on declaration of 2.nd dimension of vec of vec
            for (int i = 0; i <= n; i++)
            {
                matrix[i].resize(m+1);
            }

            // Step 2
            for (int i = 0; i <= n; i++)
            {
                matrix[i][0]=i;
            }

            for (int j = 0; j <= m; j++)
            {
                matrix[0][j]=j;
            }

            // Step 3
            for (int i = 1; i <= n; i++)
            {
                const char s_i = source[i-1];

                // Step 4
                for (int j = 1; j <= m; j++)
                {
                  const char t_j = target[j-1];

                  // Step 5
                  int cost;
                  cost = (s_i == t_j) ? 0 : 1;

                  // Step 6
                  const int above = matrix[i-1][j];
                  const int left = matrix[i][j-1];
                  const int diag = matrix[i-1][j-1];

                  int cell = std::min (above + 1, std::min(left + 1, diag + cost));

                  // Step 6A: Cover transposition, in addition to deletion,
                  // insertion and substitution. This step is taken from:
                  // Berghel, Hal ; Roach, David : "An Extension of Ukkonen's
                  // Enhanced Dynamic Programming ASM Algorithm"
                  // (http://www.acm.org/~hlb/publications/asm/asm.html)

                  if (i>2 && j>2)
                  {
                    int trans=matrix[i-2][j-2]+1;
                    if (source[i-2]!=t_j) trans++;
                    if (s_i!=target[j-2]) trans++;
                    if (cell>trans) cell=trans;
                  }

                  matrix[i][j]=cell;
                }
            }

            // Step 7
            //cpplog << "dist = " << matrix[n][m] << std::endl;
            //LOG_FLUSH
            return matrix[n][m];
        };

        template <typename String = std::string>
        struct LessDistance
        {
            String reference;

            LessDistance (const String& s) : reference(s) {}

            bool operator () (const String& left, const String& right)
            {
                //cpplog << "left = " << left << " right = " << right << std::endl;
                return pd::distance<String> (left, reference) < pd::distance<String> (right, reference);
            }
        };

        template <typename String = std::string, class Container = std::vector<String>>
        typename Container::value_type min_distance (const String& s, const Container& c)
        {
            INVALID_ARGUMENT(c.size () == 0, "c.size () = 0");

            typename Container::const_iterator it = c.begin ();
            typename Container::value_type min = *it;
            int min_dist = pd::distance<String> (min, s);
            for (; it != c.end (); ++it)
            {
                int dist = pd::distance<String> (*it, s);
                if (dist < min_dist)
                {
                    min = *it;
                    min_dist = dist;
                }
            }

            return min;
        }

        template <class Container = std::vector<char*>>
        typename Container::value_type min_distance (const char* s, const Container& c)
        {
            return min_distance (std::string(s), c);
        }

        template <typename String = std::string, class Container = std::map<std::string, std::string>>
        typename Container::value_type min_distance_map_key (const String& s, const Container& c, int max_distance = std::numeric_limits<int>::max())
        {
            INVALID_ARGUMENT(c.size () == 0, "c.size () = 0");

            typename Container::const_iterator it = c.begin ();
            std::pair<typename Container::key_type, typename Container::mapped_type> min(it->first, it->second);
            int min_dist = pd::distance<String> (min.first, s);
            for (; it != c.end (); ++it)
            {
                int dist = pd::distance<String> (it->first, s);
                if (dist < min_dist)
                {
                    min = *it;
                    min_dist = dist;
                }
            }

            std::pair<typename Container::key_type, typename Container::mapped_type> nope;
            return (min_dist <= max_distance) ? min : nope;
        }

        template <typename String = std::string, class Container = std::vector<String>, class OutContainer = std::vector<String>>
        void min_distance (const String& s, const Container& c, OutContainer& out, unsigned max_elements = 0)
        {
            INVALID_ARGUMENT(c.size () == 0, "c.size () = 0");
            LessDistance<String> ld (s);
            typedef std::multiset<String, LessDistance<String>> MSet;
            MSet mset (ld);
            for (typename Container::const_iterator it = c.begin (); it != c.end (); ++it)
            {
                mset.insert (*it);
            }
            if (max_elements == 0)
                std::copy (mset.begin (), mset.end (), std::back_inserter(out));
            else
            {
                typename MSet::iterator fim = mset.begin ();
                while (max_elements--)
                    ++fim;
                std::copy (mset.begin (), fim, std::back_inserter(out));
            }
        }

        template <class Container = std::vector<char*>, class OutContainer = std::vector<char*>>
        void min_distance (const char* s, const Container& c, OutContainer& out, unsigned max_elements = 0)
        {
            min_distance (std::string(s), c, out, max_elements);
        }
    }   // namespace cpplib
}       // namespace pensar_digital

#endif // DISTANCE_HPP_INCLUDED
