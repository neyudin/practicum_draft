#include <iostream>
template <class T> typename T::value_type process(const T &cont)
{
    auto rit = cont.crbegin();
    typename T::value_type sum = {};
    for (int i = 0; (rit != cont.crend()) && (i < 3); ++rit) {
        sum = sum + *rit;
        ++i;
    }
    return sum;
}