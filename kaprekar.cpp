#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <cmath>
#include <climits>



inline unsigned int kaprekarsConstant(int num, int width){
    
    intermediates.push_back(num);
    std::string numstring;
    while(std::count(intermediates.begin(), intermediates.end(), intermediates.back())==1){
        v_ascending.clear();v_descending.clear();
        s_ascending="";s_descending="";
        for (auto &&i:std::to_string(intermediates.back())){
            v_ascending.push_back(i-'0');
            }
        while(v_ascending.size()<width){
            v_ascending.push_back(0);
            }
        v_descending=v_ascending;
        std::sort(v_ascending.begin(), v_ascending.end());
        std::sort(v_descending.rbegin(), v_descending.rend());
        for(auto&& i: v_ascending){s_ascending+=i+'0';}
        for(auto&& i: v_descending){s_descending+=i+'0';}
        intermediates.push_back(std::stoi(s_descending)-std::stoi(s_ascending));
    }
    return intermediates.back();
}



int main(int argc, char* argv[]){
    int maxdigits=atoi(argv[1]);
    std::cout<<INT_MAX<<"\n";
    std::cout<<ULLONG_MAX<<"\n";
    std::unordered_map<int, int> last_values;
    int upperbound=(std::pow(10,maxdigits))-1;
    std::cerr<<"Upperbound"<<upperbound<<"\n";

    

    int lastnum;
    for(int i=0; i<upperbound;++i){
        lastnum=kaprekarsConstant(i, maxdigits);
        if(last_values.count(lastnum)>0){
            last_values[lastnum]+=1;
        }else{
            last_values[lastnum]=1;
        }

    }

    for (auto&& i: last_values){
        std::cout<<i.first<<","<<i.second<<"\n";
    }


}