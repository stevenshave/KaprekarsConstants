#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include "arbitaryInt.hpp"

template <int base>
class Kaprekar
{

  private:
    std::unique_ptr<ArbitaryInt> begin, end, current, ascending, descending;
    std::string firstNumber;
    std::vector<ArbitaryInt> intermediates;

  public:
    Kaprekar(size_t maxwidth)
    {
        std::cerr << "Reserving space...";
        begin = std::make_unique<ArbitaryInt>(base, maxwidth);
        end = std::make_unique<ArbitaryInt>(base, maxwidth);
        current = std::make_unique<ArbitaryInt>(base, maxwidth);
        ascending = std::make_unique<ArbitaryInt>(base, maxwidth);
        descending = std::make_unique<ArbitaryInt>(base, maxwidth);
        std::cerr << "Done\n";
    };

    void goQuickCheckForKaprekarNumbers(size_t width, int checkN)
    {
        int itercount = 0;
        begin->data.resize(width, 1);
        for (int i = 0; i < width - 1; ++i)
            begin->data[i] = 0;
        end->data.resize(width, 9);
        ascending->data.resize(width);
        descending->data.resize(width);
        current->data = begin->data;

        //Do first
        intermediates.clear();
        intermediates.push_back(*current);
        while (std::count(
                   intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
        {   
            descending = (intermediates.back().sortDescending());

            for (int i = 0; i < width; ++i)
            {
                ascending[width - 1 - i] = descending[i];
            }
            descending->subtract(ascending);
            intermediates.push_back(descending);
        }
        current++;
        ++itercount;
        firstNumber = arrayToString(intermediates.back());

        //Do the rest
        while (itercount < checkN)
        {
            intermediates.clear();
            intermediates.push_back(current);
            while (std::count(
                       intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
            {
                descending = intermediates.back().sortDescending();

            for (int i = 0; i < width; ++i)
            {
                ascending[width - 1 - i] = descending[i];
            }
            descending->subtract(ascending);
            intermediates.push_back(descending);
            }
            current++;
            ++itercount;
            if (firstNumber.compare(intermediates.back().to_string()) != 0)
                return;
        }
        if (firstNumber.compare(intermediates.back().to_string()) == 0)
        {
            std::cout << "Found - " << firstNumber << ", width=" << width << ", base=" << base << ", nchecks=" << checkN << "\n";
            return;
        }

        return;
    };
};
