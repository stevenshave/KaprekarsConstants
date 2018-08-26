#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <climits>
#include <array>
#include <fstream>
#include <cstdio>
#include <cstdlib>

class Kaprekar
{

  private:
    std::vector<int> begin, end, current, ascending, descending;
    std::vector<std::vector<int>> intermediates;

    int tmppos;
    bool tmpdone;
    bool tmpadd;
    void incrementSpecialArray(std::vector<int> &num)
    {
        tmppos = num.size() - 1;
        while (true)
        {
            if (num[tmppos] != 9)
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
    void subtractSpecialArray(std::vector<int> &high, const std::vector<int> &low)
    {
        tmppos = high.size() - 1;
        while (tmppos >= 0)
        {
            if (high[tmppos] >= low[tmppos])
            {
                high[tmppos] -= low[tmppos];
                --tmppos;
            }
            else
            {
                high[tmppos - 1] -= 1;
                high[tmppos] = (high[tmppos] + 10) - low[tmppos];
                --tmppos;
            }
        }
    }

  public:
    Kaprekar(size_t maxwidth){
        std::cerr<<"Reserving space...";
        begin.reserve(maxwidth);
        end.reserve(maxwidth);
        current.reserve(maxwidth);
        ascending.reserve(maxwidth);
        descending.reserve(maxwidth);
        std::cerr<<"Done\n";
    };

    void go(size_t width)
    {
        begin.resize(width,1);
        end.resize(width,9);
        ascending.resize(width);
        descending.resize(width);
        current=begin;
        while (true)
        {
            intermediates.clear();
            intermediates.push_back(current);
            while (std::count(
                intermediates.begin(), intermediates.end(), intermediates.back()) == 1)
            {
                tmppos = 0;
                for (int cur = 9; cur >= 0; --cur)
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

                subtractSpecialArray(descending, ascending);
                intermediates.push_back(descending);
            }
            if (intermediates[intermediates.size() - 1] != intermediates[intermediates.size() - 2])
            {
               return;
            }
            if(current==end){
                std::cerr<<"Got to the end of width="<<width<<". No loop found!  Last val="<<arrayToString(intermediates.back())<<"\n";
                exit(0);
            }
            incrementSpecialArray(current);
        }
    };

    std::string arrayToString(const std::vector<int> &in)
    {
        std::string s;
        for (int i = 0; i < in.size(); ++i)
        {
            s += std::to_string(in[i]);
        }
        return s;
    }
};

int main(int argc, char *argv[])
{
   
    Kaprekar kap((size_t)1000000);
    size_t width=10;
    while(true){
        if(width%1000==0)std::cout<<"Working on "<<width<<"\n";
        kap.go(width);
        ++width;
    }

    /* std::ofstream file;
    file.open("res-" + std::to_string(width) + ".txt", std::ios::out);
    std::cout << "writing\n";
    for (auto &&i : last_values)
    {
        std::cout << kap.arrayToString(i.first) << "," << i.second << "\n";
    }
    file.close(); */
}