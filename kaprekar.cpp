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
constexpr size_t width=533;

template < size_t width >class Kaprekar
{


private:
    
    std::array<int, width> ascending, descending;
    std::vector<std::array<int, width>> intermediates;
    std::array<int, width> begin, end, current, tmp_char_array;

    int tmppos;
    bool tmpdone;
    bool tmpadd;
    void incrementSpecialArray(std::array<int, width>& num){
        tmppos=width-1;
        while(true){
            if(num[tmppos]!=9){num[tmppos]+=1;return;}
            else{
                num[tmppos]=0;
                --tmppos;
            }
        }
    };
    void subtractSpecialArray(std::array<int, width>& high, const std::array<int, width>& low){
        tmppos=width-1;
        while(tmppos>=0){
            if(high[tmppos]>=low[tmppos]){high[tmppos]-=low[tmppos];--tmppos;}
            else{
                high[tmppos-1]-=1;
                high[tmppos]=(high[tmppos]+10)-low[tmppos];
                --tmppos;
            }
        }
    }



public:
    Kaprekar(std::array<int, width> _begin, std::array<int, width> _end){
        begin=_begin;
        end=_end;
        current=_begin;
        
    };

    std::map<std::array<int,width>,unsigned long long > go(){
        std::map<std::array<int,width>,unsigned long long > last_values;

        while(current!=end){
            intermediates.clear();
            intermediates.push_back(current);
            while(std::count(intermediates.begin(), intermediates.end(), intermediates.back())==1){
                tmppos=0;
                for(int cur=9;cur>=0;--cur){
                    for(int i=0;i<width;++i){
                        if(intermediates.back()[i]==cur){descending[tmppos]=cur; ++tmppos;}
                        }
                }
                for(int i=0;i<width;++i){
                    ascending[width-1-i]=descending[i];
                }
                subtractSpecialArray(descending, ascending);
                intermediates.push_back(descending);
            }
            if(intermediates[intermediates.size()-1]==intermediates[intermediates.size()-2]){
            if(last_values.count(intermediates.back())==1){
                last_values[intermediates.back()]+=1;
            }else{
                last_values[intermediates.back()]=1;
            }
            }
            incrementSpecialArray(current);
        }
        return last_values;
    };

    std::string arrayToString(const std::array<int, width>& in){
        std::string s;
        for (int i=0;i<width;++i){
            s+=std::to_string(in[i]);
        }
        return s;
    }
};



int main(int argc, char* argv[]){
    std::array<int,width> begin, end;
    if(argc==3){
        std::string s_begin(argv[1]);
        std::string s_end=(argv[2]);
        for(int i=0;i<width;++i)begin[i]=s_begin.at(i)-'0';
        for(int i=0;i<width;++i)end[i]=s_end.at(i)-'0';
    }

    if(argc==2){
        for(int i=0;i<width;++i)begin[i]=0;
        std::string s_end=(argv[1]);
        for(int i=0;i<width;++i)end[i]=s_end.at(i)-'0';
    }

    if(argc==1){
        for(int i=0;i<width;++i)begin[i]=0;
        for(int i=0;i<width;++i)end[i]=9;
    }

    unsigned long long base=10;
    Kaprekar<width> kap(begin,end);
    std::cout<<"Performing width = "<<width<<"\n";
   
    auto last_values=kap.go();
    
    std::ofstream file;
    file.open("res-"+std::to_string(width)+".txt");
    file<<"writing\n";
    for (auto&& i: last_values){
        file<<kap.arrayToString(i.first)<<","<<i.second<<"\n";
    }
    file.close();

}