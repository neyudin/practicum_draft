#include <iostream>
#include <stdexcept>
#include <algorithm>
template<typename T>
class Matrix {
    int rows;
    int cols;
    T *m;
    void swap(Matrix &M) {
        std::swap(rows, M.rows);
        std::swap(cols, M.cols);
        std::swap(m, M.m);
    }
public:
    const static long long ROWS_MAX = 16384;
    const static long long COLS_MAX = 16384;
    const static long long MEM_MAX = 1073741824;
    Matrix (const int r = 0, const int c = 0, const T t = {}) {
        if ((r <= 0) || (c <= 0) || (r > ROWS_MAX) || (c > COLS_MAX) || (sizeof(T) * r * c > MEM_MAX)) {
            throw std::invalid_argument("invalid argument");
        }
        rows = r;
        cols = c;
        m = new T [rows * cols];
        for (long long i = 0; i < rows * cols; ++i) {
            m[i] = t;
        }
    }
    Matrix (const Matrix &M): rows(M.rows), cols(M.cols) {
        m = new T [rows * cols];
        for (long long i = 0; i < rows * cols; ++i) {
            m[i] = M.m[i];
        }
    }
    Matrix& operator=(Matrix tmp) {
        swap(tmp);
        return *this;
    }
    int get_rows() const {
        return rows;
    }
    int get_cols() const {
        return cols;
    }
    T& at(const int r, const int c) {
        if ((r < 0) || (r >= rows) || (c < 0) || (c >= cols)) {
            throw std::range_error("range error");
        }
        return m[r * cols + c];
    }
    const T& at(const int r, const int c) const {
        if ((r < 0) || (r >= rows) || (c < 0) || (c >= cols)) {
            throw std::range_error("range error");
        }
        return m[r * cols + c];
    }
    ~Matrix() {
        delete [] m;
    }
};