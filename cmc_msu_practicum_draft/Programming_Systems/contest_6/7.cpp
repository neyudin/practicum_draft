#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
template<typename T>
class Coord
{
public:
    typedef T value_type;
    T row, col;
    Coord(T x = T(), T y = T()): row(x), col(y) {}
};
template<typename T>
T dist(Coord<T> field = Coord<T>(), Coord<T> dot1 = Coord<T>(), Coord<T> dot2 = Coord<T>()) {
    return std::max(std::min(std::abs(dot1.row - dot2.row), 
        field.row - std::abs(dot1.row - dot2.row)), 
        std::min(std::abs(dot1.col - dot2.col), field.col - std::abs(dot1.col - dot2.col)));
}