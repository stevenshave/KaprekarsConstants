#include <iostream>
#include <cmath>
#include "kaprekar.hpp"



int main(int argc, char *argv[])
{
    constexpr int base=5;
    Kaprekar<base> kap((size_t)1000000);
    size_t width = 3;
    while (true)
    {
        if (width % 1000 == 0)
            std::cout << "Working on " << width << "\n";
        kap.goQuickCheckForKaprekarNumbers(width,100);
        ++width;
    }
}