#include <iostream>
using namespace std;

struct S
{
    S(int a)
    {
        try {
            if (a > 0)
                throw *this;
            else
                if (a < 0) throw 0;
        } catch(S &) {
            cout << "1\n";
        } catch (int) {
            throw;
        }
        cout << "2\n";
    }
    S(const S &a)
    {
        cout << "3\n";
    }
    ~S()
    {
        cout << "4\n";
    }
};

int main()
{
    try {
        S s1(0), s2(5);
        cout << "5\n";
    } catch (S &) {
        cout << "6\n";
    } catch (...) {
        cout << "7\n";
    }
    return 0;
}