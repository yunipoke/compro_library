struct SCC
{
	private:
	int N;
	vector<vector<int>> G,RG;
	vector<int> component,seen,order;

	public:
	
	SCC(int N_)
	{
		N = N_;
		G.resize(N);
		RG.resize(N);
		component.assign(N,-1);
		seen.assign(N,0);
	}

	void add_edge(int u,int v)
	{
		assert(0 <= u && u < N && 0 <= v && v < N);
		G[u].push_back(v);
		RG[v].push_back(u);
	}

	int build(vector<vector<int>> &H)
	{
		for(int u = 0;u < N;u++) if(!seen[u]) dfs(u);
		reverse(order.begin(),order.end());
		int K = 0;
		for(int u : order) if(component[u] < 0)
		{
			rdfs(u,K);
			K++;
		}

		H.resize(K);
		set<pair<int,int>> connected;
		for(int u = 0;u < N;u++) 
		{
			for(int v:G[u]) if(component[u] != component[v] && !connected.count(make_pair(u,v)))
			{
				H[component[u]].push_back(component[v]);
				connected.insert(make_pair(u,v));
			}
		}

		return K;
	}

	int operator[](int u) const
	{
		assert(0 <= u && u < N);
		return component[u];
	}

	void dfs(int u)
	{
		seen[u] = 1;
		for(int v:G[u]) if(!seen[v]) dfs(v);
		order.push_back(u);
	}

	void rdfs(int u,int k)
	{
		component[u] = k;
		for(int v:RG[u]) if(component[v] < 0) rdfs(v,k);
	}
};
