#include <iostream>




template<typename T, typename C = std::less<typename std::iterator_traits<T>::value_type>>
void selection_sort(T first, T last, C comp = C()) {
    for (auto i = first; i != last; ++i) {
        auto min = i;
        auto j = i;
        for (++j; j != last; ++j) {
            if (comp(*j, *min)) {
                min = j;
            }
        }
        std::swap(*i, *min);
    }
}