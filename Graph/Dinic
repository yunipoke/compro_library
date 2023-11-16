struct Graph
{
    struct edge
    {
        int rev,from,to;
	long cap;
        edge(int r,int f,int t,long c) : rev(r),from(f),to(t),cap(c) {}
    };

    vector<vector<edge>> list;

    Graph(int n = 0) : list(n) {}

    size_t size() {return list.size();}

    vector<edge> &operator[](int i) {return list[i];}

    edge &redge(const edge &e) {return list[e.to][e.rev];}

    void run_flow(edge &e,long f)
    {
        assert(f <= e.cap);
        e.cap -= f;
        redge(e).cap += f;
    }

    void add_edge(int from,int to,long cap)
    {
        int fromrev = (int)list[from].size();
        int torev = (int)list[to].size();

        list[from].push_back(edge(torev,from,to,cap));
        list[to].push_back(edge(fromrev,to,from,0));
    }
};
template<class T>struct Dinic
{
	T INF;
	vector<int> level,iter;

	Dinic(T INF) : INF(INF) {}

	void bfs(Graph &G,int s)
	{
		level.assign((int)G.size(),-1);
		level[s] = 0;
		queue<int> Q;
		Q.push(s);
		while(!Q.empty())
		{
			int u = Q.front();
			Q.pop();

			for(int i = 0;i < (int)G[u].size();i++)
			{
				auto &e = G[u][i];
				if(e.cap && level[e.to] < 0)
				{
					level[e.to] = level[u] + 1;
					Q.push(e.to);
				}
			}
		}
	}
	
	T dfs(Graph &G,int u,int target,T f)
    	{
        	if(u == target) return f;

        	for(int &i = iter[u];i < (int)G[u].size();i++)
        	{
			auto &e = G[u][i];
           	 	if(!e.cap) continue;
			if(level[u] >= level[e.to]) continue;

			T flow = dfs(G,e.to,target,min(f,T(e.cap)));
			if(!flow) continue;

			G.run_flow(e,flow);

			return flow;
		}

		return 0;
   	}

	T maxflow(Graph &G,int s,int t)
	{
		T flow = 0;

		while(true)
		{
			bfs(G,s);
			if(level[t] < 0) return flow;
			iter.assign((int)G.size(),0);
			while(true)
			{
				T f = dfs(G,s,t,INF);
				if(!f) break;

				flow += f;
			}
		}
	}

	vector<bool> mincut(Graph G,int s)
	{
		vector<bool> res((int)G.size());
		queue<int> Q;
		Q.push(s);

		while(!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			res[u] = true;

			for(auto e:G[u]) if(e.cap && !res[e.to]) res[e.to] = true,Q.push(e.to);
		}

		return res;
	}
};
