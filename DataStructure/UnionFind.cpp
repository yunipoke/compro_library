
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
struct UnionFind
{
	private:
	int n;
	vector<int> par,siz;

	public:
	UnionFind(int n) :n(n),par(n,-1),siz(n,1) {}

	int root(int u) 
	{
		assert(0 <= u && u < n);
		return (par[u] < 0 ? u:par[u] = root(par[u]));
	}

	bool same(int u,int v)
	{
		assert(0 <= u && u < n && 0 <= v && v < n);
		return root(u) == root(v);
	}

	bool unite(int u,int v)
	{
		assert(0 <= u && u < n && 0 <= v && v < n);
		u = root(u),v = root(v);
		if(u == v) return false;

		if(siz[u] < siz[v]) swap(u,v);

		siz[u] += siz[v];
		par[v] = u;

		return true;
	}

	int size(int u)
	{
		assert(0 <= u && u < n);
		return siz[root(u)];
	}

	vector<vector<int>> components()
	{
		vector<vector<int>> ret(n);
		for(int u = 0;u < n;u++) ret[root(u)].push_back(u);

		ret.erase(remove_if(ret.begin(),ret.end(),[](vector<int> v) { return v.empty();}),ret.end());

		return ret;
	}
};
