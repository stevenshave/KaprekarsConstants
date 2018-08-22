#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <climits>
#include <array>
#include <fstream>
constexpr size_t width=6;

template < size_t width >
class Kaprekar
{
private:
    std::unordered_map<unsigned long long, unsigned long long> last_values;
    std::string s_ascending, s_descending;
    std::vector<unsigned int> v_ascending, v_descending;
    std::vector<unsigned long long> intermediates;
    unsigned long long int begin, end, current;

public:
    Kaprekar(unsigned long long _begin, unsigned long long _end){
        begin=_begin;
        end=_end;
        current=0;
    };

    std::unordered_map<unsigned long long, unsigned long long> go(){
        last_values.clear();
        
        
        while(current<=end){
            intermediates.clear();
            intermediates.push_back(current);
            
            while(std::count(intermediates.begin(), intermediates.end(), intermediates.back())==1){
                v_ascending.clear();v_descending.clear();
                s_ascending="";s_descending="";
                
                //Ensure the correct length 
                for (auto &&i:std::to_string(intermediates.back())){v_ascending.push_back(i-'0');}
                while(v_ascending.size()<width){
                    v_ascending.push_back(0);
                }
                v_descending=v_ascending;
                std::sort(v_ascending.begin(), v_ascending.end());
                std::reverse_copy(v_ascending.begin(), v_ascending.end(), v_descending.begin());
                for(auto&& i: v_ascending){s_ascending+=i+'0';}
                for(auto&& i: v_descending){s_descending+=i+'0';}
                intermediates.push_back(std::stoull(s_descending)-std::stoull(s_ascending));
            }
            if(last_values.count(intermediates.back())==1){
                last_values[intermediates.back()]+=1;
            }else{
                last_values[intermediates.back()]=1;
            }
            ++current;
        }
        return last_values;
    };
};
     
int main(int argc, char* argv[]){
    unsigned long long begin, end;
    if(argc>1){
        begin = std::stoull(argv[1]);
        end = std::stoull(argv[2]);
    }else{
        begin=0;
        end=(std::pow(10ull,width)-1);
        
    }
    std::cerr<<"Performing width = "<<width<<", between: "<<begin <<" - "<<end<<"\n";
    unsigned long long base=10;
    Kaprekar<width> kap(begin,end);
    auto last_values=kap.go();
    
    std::ofstream file;
    file.open("res-"+std::to_string(width)+","+std::to_string(begin)+"-"+std::to_string(end)+".txt");
    for (auto&& i: last_values){
        file<<i.first<<","<<i.second<<"\n";
    }
    file.close();

}