#include <iostream>
#include <limits>
#include <stdexcept>
#include <cerrno>
#include <sstream>
#include <cstdlib>
#include <string>
#include <cstring>
static const long long INT_MIN = std::numeric_limits<int>::lowest();
static const long long INT_MAX = std::numeric_limits<int>::max();
class Range {
    long long low, high;
public:
    Range(const long long l = 0, const long long h = 0): low(l), high(h) {
        if (low > high || low < INT_MIN || high < INT_MIN || low > INT_MAX || high > INT_MAX) {
            throw std::invalid_argument("invalid argument");
        }
    }
    explicit Range(const std::string &s) {
        const char *cstr = s.c_str();
        char *hstr = nullptr;
        int num = 0;
        errno = 0;
        if (cstr != nullptr && *cstr == '(') {
            low = std::strtol(cstr + 1, &hstr, 10);
            ++num;
        }
        if (hstr != nullptr && *hstr == ',') {
            high = std::strtol(hstr + 1, &hstr, 10);
            if (hstr != nullptr && *hstr == ')') {
                ++num;
            }
        }
        for (int i = 0; cstr[i] != '\0'; ++i) {
            if (std::isspace(cstr[i])) {
                throw std::invalid_argument("invalid argument");
            }
        }
        if (errno == ERANGE || low > high || low < INT_MIN || high < INT_MIN || low > INT_MAX 
            || high > INT_MAX || num != 2 || *++hstr != '\0') {
            errno = 0;
            throw std::invalid_argument("invalid argument");
        }
    }
    std::string to_string() const {
        std::ostringstream ss;
        ss << '(' << low << ',' << high << ')';
        return ss.str();
    }
    long long get_low() const {
        return low;
    }
    long long get_high() const {
        return high;
    }
    Range operator+(const Range &R1) const {
        long long nlow = low + R1.get_low();
        long long nhigh = high + R1.get_high();
        if (nlow > nhigh || nlow < INT_MIN || nhigh < INT_MIN || nlow > INT_MAX 
            || nhigh > INT_MAX) {
            throw std::range_error("range error");
        }
        Range res(nlow, nhigh);
        return res;
    }
    Range operator-(const Range &R1) const {
        long long nlow = low - R1.get_high();
        long long nhigh = high - R1.get_low();
        if (nlow > nhigh || nlow < INT_MIN || nhigh < INT_MIN || nlow > INT_MAX 
            || nhigh > INT_MAX) {
            throw std::range_error("range error");
        }
        Range res(nlow, nhigh);
        return res;
    }
    Range operator*(const Range &R1) const {
        errno = 0;
        long long mul1 = low * R1.get_low();
        long long mul2 = low * R1.get_high();
        long long mul3 = high * R1.get_low();
        long long mul4 = high * R1.get_high();
        long long nlow = std::min(std::min(mul1, mul2), std::min(mul3, mul4));
        long long nhigh = std::max(std::max(mul1, mul2), std::max(mul3, mul4));
        if (errno == ERANGE || nlow > nhigh || nlow < INT_MIN || nhigh < INT_MIN 
            || nlow > INT_MAX || nhigh > INT_MAX) {
            errno = 0;
            throw std::range_error("range error");
        }
        Range res(nlow, nhigh);
        return res;
    }
    Range operator-() const {
        long long nlow = -high;
        long long nhigh = -low;
        if (nlow > nhigh || nlow < INT_MIN || nhigh < INT_MIN || nlow > INT_MAX 
            || nhigh > INT_MAX) {
            throw std::range_error("range error");
        }
        Range res(nlow, nhigh);
        return res;
    }
    friend Range operator+(const long long, const Range &);
    friend Range operator-(const long long, const Range &);
    friend Range operator*(const long long, const Range &);
};
Range operator+(const long long a, const Range &R2) {
    if (a > 0) {
        throw std::range_error("range error");
    }
    Range R1(a);
    long long nlow = R1.get_low() + R2.get_low();
    long long nhigh = R1.get_high() + R2.get_high();
    if (nlow > nhigh || nlow < INT_MIN || nhigh < INT_MIN || nlow > INT_MAX || nhigh > INT_MAX) {
        throw std::range_error("range error");
    }
    Range res(nlow, nhigh);
    return res;
}
Range operator-(const long long a, const Range &R2) {
    if (a > 0) {
        throw std::range_error("range error");
    }
    Range R1(a);
    long long nlow = R1.get_low() - R2.get_high();
    long long nhigh = R1.get_high() - R2.get_low();
    if (nlow > nhigh || nlow < INT_MIN || nhigh < INT_MIN || nlow > INT_MAX || nhigh > INT_MAX) {
        throw std::range_error("range error");
    }
    Range res(nlow, nhigh);
    return res;
}
Range operator*(const long long a, const Range &R2) {
    if (a > 0) {
        throw std::range_error("range error");
    }
    Range R1(a);
    errno = 0;
    long long mul1 = R1.get_low() * R2.get_low();
    long long mul2 = R1.get_low() * R2.get_high();
    long long mul3 = R1.get_high() * R2.get_low();
    long long mul4 = R1.get_high() * R2.get_high();
    long long nlow = std::min(std::min(mul1, mul2), std::min(mul3, mul4));
    long long nhigh = std::max(std::max(mul1, mul2), std::max(mul3, mul4));
    if (errno == ERANGE || nlow > nhigh || nlow < INT_MIN || nhigh < INT_MIN || nlow > INT_MAX 
        || nhigh > INT_MAX) {
        errno = 0;
        throw std::range_error("range error");
    }
    Range res(nlow, nhigh);
    return res;
}

int main() {
    Range rr1(1,2), rr2(-3,4);
    std::cout << (rr1 * rr2).to_string() << std::endl;
    try {
        Range r(std::string("(-2147483649,0)"));
    }
    catch (...) {
        std::cout << "exception" << std::endl;
    }
}