#include <iostream>
#include <algorithm>
#include <cstring>
using std::string;
struct Buf {
    int ref_count;
    std::string str;
    Buf(): ref_count(1), str("") {}
    Buf(const std::string &s): ref_count(1), str(s) {}
};
class String {
    Buf *b;
public:
    String(): b(new Buf) {}
    String(const std::string &s): b(new Buf(s)) {}
    String(const char *s) {
        std::string tmp = std::string(s, strlen(s));
        b = new Buf(tmp);
    }
    String(const String &S): b(S.b) {
        b->ref_count++;
    }
    String& operator=(const String &S) {
        String tmp(S);
        std::swap(b, tmp.b);
        return *this;
    }
    String& operator+=(const String &S) {
        String obj(S);
        std::string tmp = obj.b->str;
        std::swap(b, obj.b);
        if (--b->ref_count > 0) {
            tmp = obj.b->str + tmp;
            b = new Buf(tmp);
        } else {
            b->ref_count = 1;
            b->str = obj.b->str + tmp;
        }
        return *this;
    }
    const char &operator[](const int i) const {
        return b->str[i];
    }
    char& operator[](const int i) {
        if (--b->ref_count > 0) {
            std::string tmp = b->str;
            b = new Buf(tmp);
        } else {
            b->ref_count = 1;
        }
        return b->str[i];
    }
    operator string() const {
        return b->str;
    }
    ~String() {
        if (--b->ref_count == 0) {
            delete b;
        }
    }
};