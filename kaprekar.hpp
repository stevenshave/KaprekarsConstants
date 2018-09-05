#include <vector>
#include <algorithm>
#include <string>
#include <memory>
#include "arbitaryInt.hpp"

class Kaprekar
{

  private:
    ArbitaryInt begin, end, current, ascending, descending;
    std::string firstNumber;
    std::vector<ArbitaryInt> intermediates;
    int nIters;
    int base;

  public:
    Kaprekar(int _base, size_t maxwidth, int num_iterations)
    {
        std::cerr << "Reserving space...";
        begin = ArbitaryInt(base, maxwidth);
        current = ArbitaryInt(base, maxwidth);
        ascending = ArbitaryInt(base, maxwidth);
        descending = ArbitaryInt(base, maxwidth);
        std::cerr << "Done\n";
        nIters = num_iterations;
        base = _base;
    };

    void goQuickCheckForKaprekarNumbers(size_t width)
    {
        int itercount = 0;

        //Set up begin to equal ...0001
        begin.data.resize(width);
        for (int i = 0; i < width - 1; ++i)
            begin.data[i] = 0;
        begin.data[width - 1] = 1;

       

        //Set size of temp ArbitaryInts and set current to begin
        ascending.data.resize(width);
        descending.data.resize(width);
        current=begin;

        /////////////////////////////////////////////////////////////////////////////
        //Test ...0001 number to populate firstnumber string
        
        intermediates.clear();
        intermediates.push_back(current);
    
        ascending = current;
        while (std::count(
                   intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
        {
            
            ascending.SortAscending();
            std::cerr<<ascending.to_string()<<"\n";
            exit(01);
            for (int i = 0; i < width; ++i)
            {
                descending.data[(width - 1) - i] = ascending.data[i];
            }
            descending.subtract(ascending);
            intermediates.push_back(descending);
            ascending=descending;
        }
        

        std::cerr<<"......"<<intermediates.back().to_string()<<"......."<<"\n";
        firstNumber = intermediates.back().to_string();
        /////////////////////////////////////////////////////////////////////////////
        //Start checking checkN numbers numbers in a loop
        std::cerr << "bang\n";

        while (itercount < nIters)
        {
            
            intermediates.clear();
            intermediates.push_back(current);
            ascending = intermediates.back(); //Check this works here.
            while (std::count(
                       intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
            {
                ascending.SortAscending();
                for (int i = 0; i < width; ++i)
                {
                    descending.data[width - 1 - i] = ascending.data[i];
                }
            
                descending.subtract(ascending);
                intermediates.push_back(descending);

            }
            ++current;
            ++itercount;
            //std::cerr<<"Current="<<current.to_string()<<" ascending="<<ascending.to_string()<<" descending="<<descending.to_string()<<"\n";
            //Check if a different end number has been found and if so, return.
            if (firstNumber.compare(intermediates.back().to_string()) != 0)
                return;
        }
        std::cout << "Found - " << firstNumber << ", width=" << width << ", base=" << base << ", nchecks=" << nIters << "\n";
        return;
    };
};
