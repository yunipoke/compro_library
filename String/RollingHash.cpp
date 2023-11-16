#include<iostream>
#include<random>
#include<ctime>
#include<vector>
#include<cassert>
using namespace std;

struct RollingHash
{
    static const unsigned long mod = (1UL << 61) - 1;
    static unsigned long base;
    int n;
    vector<unsigned long> hashed,pow;

    inline unsigned long mul(unsigned long a,unsigned long b) const
    {
        unsigned long au = a >> 31;
        unsigned long ad = a & ((1UL << 31)-1);
        unsigned long bu = b >> 31;
        unsigned long bd = b & ((1UL << 31)-1);
        unsigned long mid = au*bd + bu*ad;
        unsigned long midu = mid >> 30;
        unsigned long midd = mid & ((1UL << 30)-1);

        unsigned long res = au*bu*2 + midu + (midd << 31) + ad*bd;

        res = (res >> 61) + (res & mod);
        if(res >= mod) res -= mod;

        return res;
    }

    RollingHash(string &s)
    {
        n = (int)s.size();
        hashed.resize(n+1);
        pow.resize(n+1);

        pow[0] = 1;
        for(int i = 0;i < n;i++)
        {
            pow[i+1] = mul(pow[i],base);
            hashed[i+1] = mul(hashed[i],base) + s[i];

            if(hashed[i+1] >= mod) hashed[i+1] -= mod;
        }
    }

    unsigned long get(int l,int r) const
    {
        assert(0 <= l && l <= r && r <= n);

        unsigned long res = hashed[r] + mod - mul(hashed[l],pow[r-l]);
        if(res >= mod) res -= mod;

        return res;
    }

    unsigned long connect(int l1,int r1,int l2,int r2) const
    {
        unsigned long h1 = get(l1,r1);
        unsigned long h2 = get(l2,r2);

        unsigned long res = h2 + mul(h1,pow[r2-l2]);

        if(res >= mod) res -= mod;

        return res;
    }
};

mt19937_64 mt{(unsigned int)time(nullptr)};
unsigned long RollingHash::base = mt()%RollingHash::mod;
