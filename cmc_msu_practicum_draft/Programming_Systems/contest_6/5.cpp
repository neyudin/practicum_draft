#include <iostream>
#include <cstdio>
#include <algorithm>
class FileWrapper
{
    int *num;
    FILE *f;
public:
    FileWrapper(const char * s): num(nullptr) {
        f = fopen(s, "w");
        if (f) {
            num = new int (1);
        }
    }
    FileWrapper (const FileWrapper &w) {
        num = w.num;
        f = w.f;
        if (f) {
            (*num)++;
        }
    }
    FileWrapper (FileWrapper &&w) {
        num = w.num;
        f = w.f;
        w.num = nullptr;
        w.f = nullptr;
    }
    FileWrapper & operator =(FileWrapper w) {
        std::swap(w.num, num);
        std::swap(w.f, f);
        return *this;
    }
    FileWrapper& operator << (char c) {
        if (f) {
            putc(c, f);
        }
        return *this;
    }
    ~FileWrapper () {
        if (f) {
            if (*num > 1) {
                (*num)--;
            } else if (*num == 1) {
                fclose(f);
                delete num;
            }
        }
    }
};
