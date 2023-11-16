#include<iostream>
#include<vector>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<cassert>
using namespace std;


struct Edge{
    int id;
    int to; // 行き先
    long wei; // 重み

    Edge(int id,int to,long wei = 1):id(id),to(to),wei(wei) {}
};

using Graph = vector<vector<Edge>>;

template<class T,T (*op)(T,T),T (*e)()> struct SegmentTree
{
    private:
    int siz;
    vector<T> node;

    public:
    constexpr SegmentTree(int n) noexcept
    {
        siz = 1;
        while(siz < n) siz <<= 1;

        node.assign(2*siz-1,e());
    }

    constexpr void replace(int pos,T x) noexcept {func_update(pos,x,[](T u,T v){return u = v;});}

    constexpr void add(int pos,T x) noexcept {func_update(pos,x,[](T u,T v){return u+v;});}

    constexpr void func_update(int pos,T x) noexcept {func_update(pos,x,op);}
    
    constexpr void func_update(int pos,T x,T (*func)(T,T)) noexcept
    {
        assert(0 <= pos && pos < siz);
        pos += siz - 1;

        node[pos] = func(node[pos],x);

        while(pos)
        {
            pos = (pos-1)/2;
            node[pos] = op(node[2*pos+1],node[2*pos+2]);
        }
    }

    constexpr T operator [](int pos) noexcept
    {
        assert(0 <= pos && pos < siz);
        return node[pos+siz-1];
    }

    constexpr T prod(int l,int r) noexcept
    {
        assert(0 <= l && l <= r && r <= siz);

        l += siz-1;
        r += siz-1;

        T Lval = e();
        T Rval = e();

        while(l < r)
        {
            if(!(l & 1)) Lval = op(node[l++],Lval);
            if(!(r & 1)) Rval = op(node[--r],Rval);

            l >>= 1;
            r >>= 1;
        }

        return op(Lval,Rval);
    }

    constexpr T prod() noexcept {return node[0];}
};

int n;
int vs[4 << 17],depth[4 << 17],id[2 << 17],es[4 << 17],w[2 << 17];
Graph G;
long op(long a,long b){return a+b;}
long e(){return 0;}
SegmentTree<long,op,e> seg(4 << 17);

pair<int,int> op2(pair<int,int> a,pair<int,int> b){return min(a,b);}
pair<int,int> e2(){return make_pair(1 << 29,1 << 29);}
SegmentTree<pair<int,int>,op2,e2> seg2(4 << 17);

void DFS(int v,int p,int d,int &k)
{
    vs[k] = v;
    id[v] = k;
    seg2.replace(k,{d,v});
    depth[k++] = d;
    for(auto &e:G[v]) if(e.to != p)
    {
        seg.add(k,e.wei);
        es[e.id*2] = k;
        DFS(e.to,v,d+1,k);
        vs[k] = v;
        seg2.replace(k,{d,v});
        depth[k++] = d;
        seg.add(k,-e.wei);
        es[e.id*2+1] = k;
    }
}

int lca(int u,int v)
{
    u = id[u],v = id[v];
    if(u > v) swap(u,v);

    pair<int,int> p = seg2.prod(u,v+1);
    return p.second;
}

int main()
{
    cin >> n;
    G.resize(n);
    for(int i = 0;i < n-1;i++)
    {
        int u,v;
        cin >> u >> v >> w[i];
        u--; v--;
        G[u].push_back(Edge(i,v,w[i]));
        G[v].push_back(Edge(i,u,w[i]));
    }

    int k = 0;
    DFS(0,-1,0,k);

    int Q;
    cin >> Q;
    while(Q--)
    {
        int op;
        cin >> op;

        if(op == 1)
        {
            int i,nw;
            cin >> i >> nw;
            i--;
            seg.add(es[i*2],nw-w[i]);
            seg.add(es[i*2+1],-nw+w[i]);
            w[i] = nw;
        }
        else
        {
            int u,v;
            cin >> u >> v;
            u--; v--;
            int p = lca(u,v);

            long res = seg.prod(0,id[u]+1) + seg.prod(0,id[v]+1)-2*seg.prod(0,id[p]+1);

            cout << res << "\n";
        }
    }
}