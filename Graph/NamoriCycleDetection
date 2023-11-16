seen[2 << 17],fin[2 << 17];
vector<int> G[2 << 17];
void dfs(int u,int p,int &s,vector<int> &path)
{
	seen[u] = 1;
	path.push_back(u);
	for(int v:G[u])if(!fin[v] && v != p)
	{
		if(seen[v])
		{
			s = v;
			return;
		}
		else
		{
			dfs(v,u,s,path);
			if(s >= 0) return;
		}
	}
	fin[u] = 1;
	path.pop_back();
}
