#include <vector>

class ArbitaryInt
{
private:
    /* data */
    std::vector<int> data;
    int pos;
    unsigned base;
public:
    ArbitaryInt(int, size_t);
    ArbitaryInt& operator++();
};

ArbitaryInt::ArbitaryInt(int base, size_t maxlength=1000000)
{
    data.reserve(max_length);
    this.base;
}

ArbitaryInt& ArbitaryInt::operator++(){
    pos = data.size() - 1;
        while (true)
        {
            if (data[pos] != base - 1)
            {
                data[pos] += 1;
                return *this;
            }
            else
            {
                data[pos] = 0;
                if(pos==0){operator++();  return *this;}
                --pos;
            }
        }
}
