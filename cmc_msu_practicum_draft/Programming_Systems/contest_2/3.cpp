#include <iostream>
#include <cmath>
#include <cstring>

enum {
    ALLOCATED = 64
};

namespace numbers {

    class complex {

        double re, im;

    public:

        complex(double re_ = 0.0, double im_ = 0.0): re(re_), im(im_) {}

        complex(const complex &from): re(from.re), im(from.im) {}

        explicit complex(const char *str) {
            sscanf(str, "(%lf,%lf)", &re, &im);
        }

        double get_re() const {
            return re;
        }

        double get_im() const {
            return im;
        }

        double abs2() const {
            return re * re + im * im;
        }

        double abs() const {
            return sqrt(abs2());
        }

        void to_string(char *buf, size_t size) const {
            snprintf(buf, size, "(%.10g,%.10g)", re, im);
        }

        complex operator~() const {
            return complex(re, -im);
        }

        complex operator-() const {
            return complex(-re, -im);
        }

        friend complex operator+(const complex a, const complex &b) {
            return complex(a.re + b.re, a.im + b.im);
        }

        friend complex operator-(const complex a, const complex &b) {
            return complex(a.re - b.re, a.im - b.im);
        }

        friend complex operator*(const complex a, const complex &b) {
            return complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
        }

        friend complex operator/(const complex a, const complex &b) {
            return complex((a.re * b.re + a.im * b.im)/b.abs2(), 
                (a.im * b.re - a.re * b.im)/b.abs2());
        }
    };

    class complex_stack {

        complex *buf;
        complex *arr;
        int pre_alloc;
        int allocated;
        int used;

        void swap(complex_stack &tmp) {
            std::swap(buf, tmp.buf);
            std::swap(arr, tmp.arr);
            std::swap(pre_alloc, tmp.pre_alloc);
            std::swap(allocated, tmp.allocated);
            std::swap(used, tmp.used);
        }

    public:

        complex_stack(int alloc = ALLOCATED): arr(nullptr), allocated(0), used(0) {
            pre_alloc = alloc;
            buf = new complex [pre_alloc];
        }

        complex_stack(const complex_stack &from) {
            buf = new complex [from.pre_alloc];
            arr = nullptr;
            if (from.used) {
                arr = new (buf) complex [from.allocated];
                memcpy(arr, from.arr, sizeof(*arr) * from.used);
            }
            pre_alloc = from.pre_alloc;
            allocated = from.allocated;
            used = from.used;
        }

        complex_stack(complex_stack &&from): complex_stack() {
            swap(from);
        }

        ~complex_stack() {
            delete [] buf;
        }

        friend complex_stack operator<<(const complex_stack&, const complex&);

        complex_stack& operator=(complex_stack obj) {
            std::swap(buf, obj.buf);
            std::swap(arr, obj.arr);
            pre_alloc = obj.pre_alloc;
            allocated = obj.allocated;
            used = obj.used;
            return *this;
        }

        complex_stack operator~() const {
            complex_stack res(pre_alloc);
            res.used = used;
            if (res.used) {
                --res.used;
            }
            if (res.used) {
                res.allocated = allocated;
                res.arr = new (res.buf) complex [res.allocated];
                memcpy(res.arr, arr, sizeof(*res.arr) * res.used);
            }
            return res;
        }

        complex& operator+() const {
            if (used) {
                return arr[used - 1];
            }
            return *arr;
        }

        complex& operator[](int i) const {
            return arr[i];
        }

        size_t size() const {
            return used;
        }
    };

    complex_stack operator<<(const complex_stack &to, const complex &from) {
        int pre_size = to.pre_alloc;
        int size = to.allocated;
        if (!size) {
            size = 1;
        }
        if (to.used + 1 > size) {
            size *= 2;
        }
        if (size > pre_size) {
            pre_size *= 4;
        }
        complex_stack res(pre_size);
        res.arr = new (res.buf) complex [size];
        res.allocated = size;
        if (to.arr) {
            memcpy(res.arr, to.arr, sizeof(*res.arr) * to.used);
            res.used = to.used;
        }
        res.arr[res.used++] = from;
        return res;
    }

    complex eval(char **args, const complex &z) {
        complex_stack stack;
        for (int i = 0; args[i]; ++i) {
            if (args[i][0] == '(') {
                complex tmp = complex(args[i]);
                stack = stack << tmp;
                continue;
            }
            if (args[i][0] == 'z') {
                stack = stack << z;
                continue;
            }
            if (args[i][0] == '+') {
                complex tmp = stack[stack.size() - 2];
                tmp = tmp + (+stack);
                stack = ~~stack;
                stack = stack << tmp;
                continue;
            }
            if (args[i][0] == '-') {
                complex tmp = stack[stack.size() - 2];
                tmp = tmp - (+stack);
                stack = ~~stack;
                stack = stack << tmp;
                continue;
            }
            if (args[i][0] == '*') {
                complex tmp = stack[stack.size() - 2];
                tmp = tmp * (+stack);
                stack = ~~stack;
                stack = stack << tmp;
                continue;
            }
            if (args[i][0] == '/') {
                complex tmp = stack[stack.size() - 2];
                tmp = tmp / (+stack);
                stack = ~~stack;
                stack = stack << tmp;
                continue;
            }
            if (args[i][0] == '!') {
                stack = stack << (+stack);
                continue;
            }
            if (args[i][0] == ';') {
                stack = ~stack;
                continue;
            }
            if (args[i][0] == '~') {
                complex tmp = ~(+stack);
                stack = ~stack;
                stack = stack << tmp;
                continue;
            }
            if (args[i][0] == '#') {
                complex tmp = -(+stack);
                stack = ~stack;
                stack = stack << tmp;
                continue;
            }
        }
        return +stack;
    }
}