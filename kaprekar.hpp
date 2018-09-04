#include <vector>
#include <algorithm>
#include <string>
#include "arbitaryInt.hpp"
template <int base>
class Kaprekar
{

  private:
    std::vector<int> begin, end, current, ascending, descending;
    std::string firstNumber;
    std::vector<std::vector<int>> intermediates;
    int tmppos;
    bool tmpdone;
    bool tmpadd;

    std::string arrayToString(const std::vector<int> &in)
    {
        std::string s;
        for (int i = 0; i < in.size(); ++i)
        {
            s += std::to_string(in[i]);
        }
        return s;
    };

    void incrementSpecialArray(std::vector<int> &num)
    {
        tmppos = num.size() - 1;
        while (true)
        {
            if (num[tmppos] != base - 1)
            {
                num[tmppos] += 1;
                return;
            }
            else
            {
                num[tmppos] = 0;
                --tmppos;
            }
        }
    };

  public:
    Kaprekar(size_t maxwidth)
    {
        std::cerr << "Reserving space...";
        begin.reserve(maxwidth);
        end.reserve(maxwidth);
        current.reserve(maxwidth);
        ascending.reserve(maxwidth);
        descending.reserve(maxwidth);

        std::cerr << "Done\n";
    };

    void goQuickCheckForKaprekarNumbers(size_t width, int checkN)
    {
        int itercount = 0;
        begin.resize(width, 1);
        for (int i = 0; i < width - 1; ++i)
            begin[i] = 0;
        end.resize(width, 9);
        ascending.resize(width);
        descending.resize(width);
        current = begin;

        auto makeDescendingAndAscendingFromLastIntermediate = [&]() {
            tmppos = 0;
            for (int cur = base - 1; cur >= 0; --cur)
            {
                for (int i = 0; i < width; ++i)
                {
                    if (intermediates.back()[i] == cur)
                    {
                        descending[tmppos] = cur;
                        ++tmppos;
                    }
                }
            }
            for (int i = 0; i < width; ++i)
            {
                ascending[width - 1 - i] = descending[i];
            }
        };
        auto subtractAscendingFromDescending = [&]() {
            tmppos = descending.size() - 1;
            while (tmppos >= 0)
            {
                if (descending[tmppos] >= ascending[tmppos])
                {
                    descending[tmppos] -= ascending[tmppos];
                    --tmppos;
                }
                else
                {
                    descending[tmppos - 1] -= 1;
                    descending[tmppos] = (descending[tmppos] + base) - ascending[tmppos];
                    --tmppos;
                }
            }
        };

        //Do first
        intermediates.clear();
        intermediates.push_back(current);
        while (std::count(
                   intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
        {
            makeDescendingAndAscendingFromLastIntermediate();
            subtractAscendingFromDescending();
            intermediates.push_back(descending);
        }
        incrementSpecialArray(current);
        ++itercount;
        firstNumber=arrayToString(intermediates.back());

        //Do the rest
        while (itercount < checkN)
        {
            intermediates.clear();
            intermediates.push_back(current);
            while (std::count(
                       intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
            {
                makeDescendingAndAscendingFromLastIntermediate();
                subtractAscendingFromDescending();
                intermediates.push_back(descending);
            }
            incrementSpecialArray(current);
            ++itercount;
            if(firstNumber.compare(arrayToString(intermediates.back()))!=0)return;
        }
        if(firstNumber.compare(arrayToString(intermediates.back()))==0){std::cout<<"Found - "<<firstNumber<<", width="<<width<<", base="<<base<<", nchecks="<<checkN<<"\n";return;}   

    return;
    };
};
