#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>

int main()
{
    int n = 0;
    double sum = 0.0, sqr_sum = 0.0, x = 0.0;
    while (std::cin >> x) {
        sum += x;
        sqr_sum += x * x;
        ++n;
    }
    double sigma = std::sqrt(std::abs(sqr_sum/n - sum/n * sum/n));
    std::cout << std::setprecision(10) << sum/n << std::endl << sigma << std::endl;
}