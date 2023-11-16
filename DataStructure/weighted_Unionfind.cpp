#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<cassert>
#include<cmath>
#include<numeric>
#include<iomanip>
using namespace std;
template<class T>
struct WeightedUnionFind{

    vector<int> par,siz;
    vector<T> diff_weight;

    WeightedUnionFind(int n)
    {
        par.resize(n),siz.assign(n,1),diff_weight.resize(n);
        iota(par.begin(),par.end(),0);
    }

    int root(int x)
    {
        if(par[x] == x) return x;
        root(par[x]);
        diff_weight[x] += diff_weight[par[x]];
        return par[x] = root(par[x]);
    }

    T weight(int x)
    {
        root(x);
        return diff_weight[x];
    }

    bool same(int x,int y)
    {
        return root(x) == root(y);
    }

    bool unite(int x,int y,long w)
    {
        w += weight(x); w -= weight(y);
        x = root(x); y = root(y);
        if(x == y) return false;

        if(siz[x] < siz[y]) swap(x,y),w *= -1;
        par[y] = x;
        siz[x] += siz[y];
        diff_weight[y] = w;
        return true;
    }

    int size(int x)
    {
        return siz[root(x)];
    }

    T diff(int x,int y)
    {
        assert(same(x,y));
        return weight(y)-weight(x);
    }
};

/* int main() */
/* { */
/*     ios::sync_with_stdio(false); */
/*     cin.tie(nullptr); */

/*     int n,m; */
/*     cin >> n >> m; */
/* 	 WeightedUnionFind<long long> uf(n); */
/*     for(int i = 0;i < m;i++) */
/*     { */
/*         int l,r,d; */
/*         cin >> l >> r >> d; */
/*         l--; r--; */
/*         if(uf.same(l,r)) */
/*         { */
/*             long long diff = uf.diff(l,r); */
/*             if(diff != d) */
/*             { */
/*                 cout << "No" << endl; */
/*                 return 0; */
/*             } */
/*         } */
/*         else */
/*         { */
/*             uf.unite(l,r,d); */
/*         } */
/*     } */

/*     cout << "Yes" << endl; */
/* } */
