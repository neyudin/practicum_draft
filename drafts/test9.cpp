#include <iostream>
using namespace std;
struct A {
	mutable int x, y;
	A(int a): x(a), y(a) {}
	int f(int a) const {
		return x + y + a;
	}
};
int main() {
	const A a(1);
	a.x = 3;
	cout << a.x << a.f(1) << a.y << endl;
	return 0;
}
