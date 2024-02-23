struct CentroidDecomposition
{
	private:
	int N;
	vector<vector<int>> G;
	vector<int> seen,subtree;

	void calc_subtree(int u,int p) 
	{
		subtree[u] = 1;
		for(int v : G[u])
		{
			if(v == p || seen[v])
			{
				continue;
			}
			calc_subtree(v,u);
			subtree[u] += subtree[v];
		}
	}

	int find_centroid(int u,int p,const int total_size)
	{
		for(int v : G[u])
		{
			if(v == p || seen[v])
			{
				continue;
			}
			if(subtree[v] * 2 > total_size)
			{
				return find_centroid(v,u,total_size);
			}
		}
		return u;
	}

	public:

	CentroidDecomposition(int N) : N(N),G(N),seen(N),subtree(N) {}

	void add_edge(int u,int v)
	{
		assert(0 <= u && u < N && 0 <= v && v < N);
		G[u].push_back(v);
		G[v].push_back(u);
	}

	int build(vector<vector<int>> &H,int u)
	{
		static bool first_call = true;
		if(first_call)
		{
			first_call = false;
			H.resize(N);
		}
		calc_subtree(u,-1);
		int total_size = subtree[u];
		int centroid = find_centroid(u,-1,total_size);
		seen[centroid] = 1;
		for(int v : G[centroid])
		{
			if(seen[v])
			{
				continue;
			}
			int next_centroid = build(H,v);
			H[centroid].push_back(next_centroid);
		}
		return centroid;
	}
};
