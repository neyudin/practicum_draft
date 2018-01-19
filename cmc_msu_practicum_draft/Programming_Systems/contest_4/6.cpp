#include <iostream>
template <typename T>
void myreverse(T begin, T end)
{
    while ((begin != end) && (begin != --end)) {
        std::swap(*begin++, *end);
    }
}