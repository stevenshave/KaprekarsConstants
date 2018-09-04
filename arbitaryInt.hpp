#include <vector>

class ArbitaryInt
{
  private:
    std::vector<int> tmpdata;
    /* data */
    int pos;
    unsigned base;

  public:
    std::vector<int> data;
    inline void subtract(const ArbitaryInt &&r)
    {
        pos = data.size() - 1;
        while (pos >= 0)
        {
            if (data[pos] >= r.data[pos])
            {
                data[pos] -= r.data[pos];
                --pos;
            }
            else
            {
                data[pos - 1] -= 1;
                data[pos] = (data[pos] + base) - r.data[pos];
                --pos;
            }
        }
    };

    ArbitaryInt &operator=(ArbitaryInt const &r)
    {
        if (&r != this)
        {
            data = r.data;
            pos = r.pos;
            base = r.base;
            tmpdata=r.tmpdata;
        }
        return *this;
    };

    std::string to_string()
    {
        std::string s;
        s += std::to_string(data[0]);
        for (int i = 1; i < data.size(); ++i)
        {
            s += "," + std::to_string(data[i]);
        }
        return s;
    };

    ArbitaryInt(int numberbase, size_t maxlength = 1000000)
    {
        data.reserve(maxlength);
        tmpdata.reserve(maxlength);
        base = numberbase;
    };

    ArbitaryInt &operator++()
    {
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
                if (pos == 0)
                {
                    operator++();
                    return *this;
                }
                --pos;
            }
        }
    };

    void SortDescending()
    {
        pos = 0;
        for (int cur = base - 1; cur >= 0; --cur)
        {
            for (int i = 0; i < data.size(); ++i)
            {
                if (data[i] == cur)
                {
                    tmpdata[pos] = cur;
                    ++pos;
                }
            }
        }
        data.swap(tmpdata);
    };
};
