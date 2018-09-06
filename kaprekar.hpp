#include <vector>
#include <algorithm>
#include <string>
#include <memory>
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    os << "[";
    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii)
    {
        os << " " << *ii;
    }
    os << " ]";
    return os;
};
class Kaprekar
{
  private:
    constexpr static size_t maxlength = 1000000;
    std::vector<int> begin, end, current, ascending, descending, tmpdata, firstnumber;
    std::vector<std::vector<int>> intermediates;
    int nIters;
    int base;
    int pos; //Used for SortDescending

  public:
    Kaprekar(int _base, int num_iterations)
    {
        std::cerr << "Reserving space...";
        begin.reserve(maxlength);
        current.reserve(maxlength);
        ascending.reserve(maxlength);
        descending.reserve(maxlength);
        tmpdata.reserve(maxlength);
        intermediates.reserve(1000);
        std::cerr << "Done\n";
        nIters = num_iterations;
        base = _base;
    };

    inline void SortDescending()
    {
        pos = 0;
        for (int cur = base - 1; cur >= 0; --cur)
        {
            for (int i = 0; i < descending.size(); ++i)
            {
                if (descending[i] == cur)
                {
                    tmpdata[pos] = cur;
                    ++pos;
                }
            }
        }
        descending = tmpdata;
    };

    inline void subtractAfromD()
    {
        pos = descending.size() - 1;
        while (pos >= 0)
        {
            if (descending[pos] >= ascending[pos])
            {
                descending[pos] -= ascending[pos];
                --pos;
            }
            else
            {
                descending[pos - 1] -= 1;
                descending[pos] = (descending[pos] + base) - ascending[pos];
                --pos;
            }
        }
    };

    inline void IncrementCurrent()
    {
        pos = current.size() - 1;
        while (true)
        {
            if (current[pos] != base - 1)
            {
                current[pos] += 1;
                if (std::count(current.begin(), current.end(), current[0]) == current.size())
                    IncrementCurrent();
                return;
            }
            else
            {
                current[pos] = 0;
                if (pos == 0)
                {
                    IncrementCurrent();
                    if (std::count(current.begin(), current.end(), current[0]) == current.size())
                        IncrementCurrent();
                    return;
                }
                --pos;
            }
        }
    };

    void goQuickCheckForKaprekarNumbers(size_t width)
    {
        int itercount = 0;

        //Set up begin to equal ...0001
        begin.resize(width);
        for (int i = 0; i < width - 1; ++i)
            begin[i] = 0;
        begin[width - 1] = 1;

        //Set size of temp ArbitaryInts and set current to begin
        ascending.resize(width);
        descending.resize(width);
        tmpdata.resize(width);
        current = begin;

        /////////////////////////////////////////////////////////////////////////////
        //Test ...0001 number to populate firstnumber string

        intermediates.clear();
        intermediates.push_back(current);

        descending = current;
        while (std::count(
                   intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
        {
            SortDescending();
            //exit(01);
            for (int i = 0; i < width; ++i)
            {
                ascending[(width - 1) - i] = descending[i];
            }
            subtractAfromD();
            intermediates.push_back(descending);
        }
        firstnumber = descending;
        IncrementCurrent();

        /////////////////////////////////////////////////////////////////////////////
        //Start checking checkN numbers numbers in a loop
        while (itercount < nIters)
        {
            intermediates.clear();
            intermediates.push_back(current);
            descending = intermediates.back(); //Check this works here.
            while (std::count(
                       intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
            {
                SortDescending();
                for (int i = 0; i < width; ++i)
                {
                    ascending[width - 1 - i] = descending[i];
                }

                subtractAfromD();
                intermediates.push_back(descending);
            }
            IncrementCurrent();
            ++itercount;
            //Check if a different end number has been found and if so, return.
            if (firstnumber != intermediates.back())
                return;
        }
        std::cout << "Found - " << firstnumber << ", width=" << width << ", base=" << base << ", nchecks=" << nIters << "\n";
        return;
    };
};
