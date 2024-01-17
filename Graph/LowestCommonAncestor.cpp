
struct LCA
{
	private:
	int N,K;
	vector<vector<int>> G;
	vector<vector<int>> par;
	vector<int> depth;
	int edge_count;

	void dfs(int u,int p)
	{
		par[0][u] = p;
		if(p != -1)
		{
			depth[u] = depth[p] + 1;
		}


		for(int v : G[u]) if(v != p)
		{
			dfs(v,u);
		}
	}

	public:
	LCA() {}
	LCA(int N_)
	{
		N = N_;
		int M = 1;
		K = 0;
		while(M < N)
		{
			M <<= 1;
			K++;
		}
		par.assign(K,vector<int>(N,-1));
		G.resize(N);
		depth.assign(N,0);
		edge_count = 0;
	}

	void add_edge(int u,int v,bool oriented = false)
	{
		assert(0 <= u && u < N && 0 <= v && v < N);
		G[u].push_back(v);
		if(!oriented)
		{
			G[v].push_back(u);
		}
		edge_count++;
	}

	void build(int root = 0)
	{
		assert(0 <= root && root < N);
		assert(edge_count == N - 1);

		dfs(root,-1);

		for(int k = 1;k < K;k++)
		{
			for(int u = 0;u < N;u++) if(par[k - 1][u] != -1)
			{
				par[k][u] = par[k - 1][par[k - 1][u]];
			}
		}
	}

	int lca(int u,int v)
	{
		assert(0 <= u && u < N && 0 <= v && v < N);

		if(depth[u] < depth[v])
		{
			swap(u,v);
		}

		for(int k = 0;k < K;k++)
		{
			if((depth[v] - depth[u]) >> k & 1)
			{
				u = par[k][u];
			}
		}

		if(u == v)
		{
			return u;
		}

		for(int k = K;k--;)
		{
			if(par[k][u] == par[k][v]);
			else
			{
				u = par[k][u];
				v = par[k][v];
			}
		}

		assert(par[0][u] == par[0][v]);
		return par[0][u];
	}

	int get_depth(int u)
	{
		assert(0 <= u && u < N);
		return depth[u];
	}
};
