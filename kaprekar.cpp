#include <iostream>
#include <cmath>

#include "kaprekar.hpp"

int main(int argc, char *argv[])
{

    // ArbitaryInt a(10, 100);
    // a.data.resize(4);
    // a.data={1,9,3,2};
    // std::cerr<<a.to_string()<<"\n";
    // a.SortAscending();
    // std::cerr<<a.to_string()<<"\n";

    int base = 10;
    int maxwidth = 10000;
    int num_iterations = 1000;
    Kaprekar kap(base, num_iterations);
    size_t width = 2;
    while (true)
    {
        if (width % 1000 == 0)
            std::cout << "Working on " << width << "\n";
        kap.goQuickCheckForKaprekarNumbers(width);
        ++width;
    }
}