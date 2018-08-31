#include <iostream>
#include <cmath>

#include "kaprekar.hpp"



int main(int argc, char *argv[])
{
    constexpr int base=4;
    Kaprekar<base> kap((size_t)1000000);
    size_t width = 4;
    while (true)
    {
        if (width % 1000 == 0)
            std::cout << "Working on " << width << "\n";
        kap.goQuickCheckForKaprekarNumbers(width,10);
        ++width;
    }
}