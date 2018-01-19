#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>

namespace numbers
{
    class complex
    {
        double re_, im_;
    public:
        complex(double re = 0.0, double im = 0.0): re_(re), im_(im) {}
        complex(const complex &from): re_(from.re_), im_(from.im_) {}
        explicit complex(const char *str) {
            sscanf(str, "(%lf,%lf)", &re_, &im_);
        }
        double get_re() const {
            return re_;
        }
        double get_im() const {
            return im_;
        }
        double abs2() const {
            return re_ * re_ + im_ * im_;
        }
        double abs() const {
            return sqrt(abs2());
        }
        void to_string(char *buf, size_t size) const {
            snprintf(buf, size, "(%.10g,%.10g)", re_, im_);
        }
        complex operator~() const {
            return complex(re_, -im_);
        }
        complex operator-() const {
            return complex(-re_, -im_);
        }
        friend complex operator+(const complex a, const complex &b);
        friend complex operator-(const complex a, const complex &b);
        friend complex operator*(const complex a, const complex &b);
        friend complex operator/(const complex a, const complex &b);
    };

    complex operator+(const complex a, const complex &b) {
        return complex(a.re_ + b.re_, a.im_ + b.im_);
    }
    complex operator-(const complex a, const complex &b) {
        return complex(a.re_ - b.re_, a.im_ - b.im_);
    }
    complex operator*(const complex a, const complex &b) {
        return complex(a.re_ * b.re_ - a.im_ * b.im_, a.re_ * b.im_ + a.im_ * b.re_);
    }
    complex operator/(const complex a, const complex &b) {
        return complex((a.re_ * b.re_ + a.im_ * b.im_)/(b.re_ * b.re_ + b.im_ * b.im_), 
            (a.im_ * b.re_ - a.re_ * b.im_)/(b.re_ * b.re_ + b.im_ * b.im_));
    }
}