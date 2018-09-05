#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include "arbitaryInt.hpp"

template <int base>
class Kaprekar
{

  private:
    ArbitaryInt begin, end, current, ascending, descending;
    std::string firstNumber;
    std::vector<ArbitaryInt> intermediates;
    int nIters;

  public:
    Kaprekar(int base, size_t maxwidth, int num_iterations)
    {
        std::cerr << "Reserving space...";
        begin = ArbitaryInt(base, maxwidth);
        end = ArbitaryInt(base, maxwidth);
        current = ArbitaryInt(base, maxwidth);
        ascending = ArbitaryInt(base, maxwidth);
        descending = ArbitaryInt(base, maxwidth);
        std::cerr << "Done\n";
        nIters=num_iterations;
    };

    void goQuickCheckForKaprekarNumbers(size_t width, int checkN)
    {
        int itercount = 0;
        
        //Set up begin to equal ...0001
        begin.data.resize(width);
        for (int i = 0; i < width - 1; ++i)
            begin.data[i] = 0;
        begin.data[width - 1] = 1;

        //Set up end to equal ...9999
        end.data.resize(width);
        for (int i = 0; i < width - 1; ++i)
            end.data[i] = 9;

        //Set size of temp ArbitaryInts and set current to begin    
        ascending.data.resize(width);
        descending.data.resize(width);
        current.data = begin.data;

        //Now do 1 iteration to populate intermediates[0]
        intermediates.clear();
        intermediates.push_back(current);
        while (std::count(
                   intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
        {
            descending = intermediates.back();
                descending.SortDescending();

            for (int i = 0; i < width; ++i)
            {
                ascending[width - 1 - i] = descending[i];
            }
            descending.subtract(ascending);
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
                descending = intermediates.back();
                descending.SortDescending();
                for (int i = 0; i < width; ++i)
                {
                    ascending[width - 1 - i] = descending[i];
                }
                descending.subtract(ascending);
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
