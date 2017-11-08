#include "dummy.h"

namespace pensar_digital
{
    namespace cpplib
    {
        namespace test
        {
            bool operator== (const Dummy& left, const Dummy& right)
            {
                bool ok;

                ok = (left.s == right.s);
                ok = ok && (left.i == right.i);
                if (ok)
                    ok = ok && (left.slist == right.slist);

                return ok;
            }
        }
    }
}
