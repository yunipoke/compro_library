
struct Edge{
    int to; // 行き先
    long wei; // 重み

    Edge(int to,long wei = 1):to(to),wei(wei) {}
};

using Graph = vector<vector<Edge>>;

struct Tree{
    private:
    int n;
    template<class T> inline bool chmax(T &a,T b){if(a < b){a = b; return true;} return false;}
    
    public:
    vector<vector<int>> par; // par[i][j] -> 頂点iから2^j個だけ登った頂点
    vector<int> depth; // 根からの深さ
    vector<long> Wdepth; // 根からの重み付き深さ
    vector<int> subtree; //その頂点を根とした部分木(自身も含む)の大きさ

    Tree(const Graph &G,int root = 0) {init(G,root);}

    void init(const Graph &G,int root = 0)
    {
        n = (int)G.size();
        int k = 1;

        while((1 << k) < n) k++; // n以上の最小の2の冪の指数だけ確保しておけば最悪の場合も根には辿り着ける

        par.assign(n,vector<int>(k,-1)); // -1はそれ以上登れないことを示す
        depth.assign(n,-1);
        Wdepth.assign(n,-1);
        subtree.assign(n,0);

        DFS(G,root,-1,0);

        for(int j = 0;j+1 < k;j++){
            for(int i = 0;i < n;i++){
                // 2^j個登ってはみ出るなら当然2^(j+1)登ってもはみ出る
                if(par[i][j] < 0){
                    par[i][j+1] = -1;
                }else{ // 2^(j+1)登る = 2^j登ってさらに2^j登る
                    par[i][j+1] = par[par[i][j]][j];
                }
            }
        }
    }

    // DFSで深さを求める
    int DFS(const Graph &G,int v,int p,int d,long w = 1)
    {
        par[v][0] = p;
        depth[v] = d;
        Wdepth[v] = w;

        int res = 1;

        for(auto e:G[v]){
            if(e.to == p) continue;

            res += DFS(G,e.to,v,d + 1,w + e.wei);
        }

        return subtree[v] = res;
    }

    // 最小共通祖先
    int lca(int u,int v)
    {
        assert(0 <= u && u < n && 0 <= v && v < n);

        if(depth[u] < depth[v]) swap(u,v);
        int k = (int)par[0].size();

        // 深さの差を2の冪で埋めていく
        for(int j = 0;j < k;j++){
            if((depth[u]-depth[v]) & 1 << j) u = par[u][j];
        }

        // そこで出会う場合
        if(u == v) return u;

        // 真上にlcaがいる状態まで進む
        for(int j = k-1;j >= 0;j--){
            if(par[u][j] != par[v][j]){
                u = par[u][j];
                v = par[v][j];
            }
        }

        // 真上を返す
        return par[u][0];
    }

    // 頂点uとvの最短距離を返す
    int dist(int u,int v)
    {
        int x = lca(u,v);
        return depth[u] + depth[v] - 2*depth[x];
    }

    // 頂点uとvの重み付き最短距離を返す
    long Wdist(int u,int v)
    {
        int x = lca(u,v);
        return Wdepth[u] + Wdepth[v] - 2*Wdepth[x];
    }

    // 頂点xが頂点uとvの最短路上にいるかどうか
    bool onpath(int u,int v,int x)
    {
        return dist(u,x) + dist(x,v) == dist(u,v);
    }

    // 木の直径を返す
    int diameter()
    {
        int ret = -1;
        int u;
        for(int v = 0;v < n;v++) if(chmax(ret,dist(0,v))) u = v;

        ret = -1;
        for(int v = 0;v < n;v++) chmax(ret,dist(u,v));

        return ret;
    }
};

// TreeGraph::n = G.size()としているのでグローバルにGを定義するべからず