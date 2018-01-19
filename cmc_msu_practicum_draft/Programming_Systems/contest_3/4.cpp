#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>

class Sum {
	double s;
public:
	Sum(): s(0) {}
	void operator () (double n) {
		s += n;
	}
	double get() {
		return s;
	}
};

int main() {
	std::vector<double> v;
	double n;
	while (std::cin >> n) {
		v.push_back(n);
	}
	int num = v.size() * 0.1;
	v.erase(v.begin(), v.begin() + num);
	v.erase(v.end() - num, v.end());
	std::sort(v.begin(), v.end());
	num = v.size() * 0.1;
	v.erase(v.begin(), v.begin() + num);
	v.erase(v.end() - num, v.end());
	Sum sum = std::for_each(v.begin(), v.end(), Sum());
	std::cout << std::setprecision(10) << sum.get() / v.size() << std::endl;
}