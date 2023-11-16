#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
int n,m,seen[2 << 17],k = 0;
vector<int> order,component(2 << 17,-1);
vector<vector<int>> G(2 << 17),rG(2 << 17);
int siz[2 << 17],memo[2 << 17];

void DFS(int v)
{
    seen[v] = 1;
    for(int nv:G[v]) if(!seen[nv]) DFS(nv);
    order.push_back(v);
}

void rDFS(int v)
{
    component[v] = k;
    for(int nv:rG[v])if(component[nv] < 0) rDFS(nv);
}

vector<vector<int>> rebuild()
{
    int N = *max_element(component.begin(),component.end()) + 1;
    vector<vector<int>> res(N);
    set<pair<int,int>> connect;

    for(int v = 0;v < n;v++)
    {
        for(int nv:G[v])
        {
            if(component[v] != component[nv] && !connect.count(make_pair(v,nv)))
            {
                res[component[v]].push_back(component[nv]);
                connect.insert(make_pair(v,nv));
            }
        }
    }

    return res;
}

int f(int v,vector<vector<int>> &reG)
{
    if(siz[v] > 1) return 1;
    if(memo[v] >= 0) return memo[v];

    for(int nv:reG[v])
    {
        if(f(nv,reG)) return memo[v] = 1;
    }

    return memo[v] = 0;
}

int main()
{
    cin >> n >> m;
    for(int i = 0;i < m;i++)
    {
        int u,v;
        cin >> u >> v;
        u--; v--;
        G[u].push_back(v);
        rG[v].push_back(u);
    }

    for(int v = 0;v < n;v++)
    {
        if(!seen[v])DFS(v);
    }

    reverse(order.begin(),order.end());

    for(int v:order)
    {
        if(component[v] < 0)
        {
            rDFS(v);
            k++;
        }
    }

    int N = 0;
    for(int v = 0;v < n;v++)
    {
        siz[component[v]]++;
        N = max(component[v],N);
    }

    auto reG = rebuild();
    N++;
    int res = 0;

    for(int v = 0;v < N;v++) memo[v] = -1;

    for(int v = 0;v < N;v++)
    {
        if(f(v,reG)) res += siz[v];
    }

    cout << res << endl;
}