template<class T,T (*op)(T,T),T e(),class F,T (*mapping)(F,T),F (*composition)(F,F),F id()> struct LazySegmentTree
{
    private:
    vector<T> node;
    vector<F> lazy;
    int siz,log;

    void map_and_comp(F f,int u)
    {
        node[u] = mapping(f,node[u]);
        if(u < siz) lazy[u] = composition(f,lazy[u]);
    }

    void propagate(int u)
    {
        assert(0 <= u && u < siz);

        map_and_comp(lazy[u],2*u);
        map_and_comp(lazy[u],2*u+1);

        lazy[u] = id();
    }

    void recalculate(int u) {node[u] = op(node[2*u],node[2*u+1]);}

    public:
    LazySegmentTree(int n = 0) : LazySegmentTree(vector<T>(n,e())) {}
    LazySegmentTree(const vector<T> &V)
    {
	    siz = 1;
	    log = 0;
	    while(siz < (int)V.size()) siz <<= 1,log++;
	    node.assign(2*siz,e());
	    lazy.assign(siz,id());
	    for(int i = 0;i < (int)V.size();i++) node[i+siz] = V[i];
	    for(int i = siz-1;i >= 1;i--) recalculate(i);
    }

    void fill(T x,int l = 0,int r = -1) {if(r < 0){r = siz;} for(int i = l;i < r;i++) replace(i,x);}

    void clear() {fill(e());}

    void replace(int pos,T x) {func_update(pos,x,[](T u,T v){return u = v;});}

    void add(int pos,T x) {func_update(pos,x,[](T u,T v){return u + v;});}

    void func_update(int pos,T x,T (*func)(T,T))
    {
        assert(0 <= pos && pos < siz);
        pos += siz;

        for(int i = log;i >= 1;i--) propagate(pos >> i);

        node[pos] = func(node[pos],x);

        for(int i = 1;i <= log;i++) recalculate(pos >> i);
    }

    T operator[](int pos)
    {
        assert(0 <= pos && pos < siz);

        pos += siz;
        for(int i = log;i >= 1;i--) propagate(pos >> i);
        return node[pos];
    }

    void apply(int pos,F f)
    {
        assert(0 <= pos && pos < siz);
        pos += siz;

        for(int i = log;i >= 1;i--) propagate(pos >> i);

        node[pos] = mapping(f,node[pos]);

        for(int i = 1;i <= log;i++) recalculate(pos >> i);
    }

    void apply(int l,int r,F f)
    {
        assert(0 <= l && l <= r && r <= siz);
        if(l == r) return;

        l += siz;
        r += siz;

        int l0 = l/(l & -l);
        int r0 = r/(r & -r);

        for(int i = log;i >= 1;i--) propagate(l0 >> i);
        for(int i = log;i >= 1;i--) propagate((r0-1) >> i);

        while(l < r)
        {
            if(l & 1) map_and_comp(f,l++);
            if(r & 1) map_and_comp(f,--r);

            l >>= 1;
            r >>= 1;
        }

        for(int i = 1;i <= log;i++) recalculate(l0 >> i);
        for(int i = 1;i <= log;i++) recalculate((r0-1) >> i);
    }

    T prod() {return node[1];}

    T prod(int l,int r)
    {
        assert(0 <= l && l <= r && r <= siz);

        l += siz;
        r += siz;

        int l0 = l/(l & -l);
        int r0 = r/(r & -r);

        for(int i = log;i >= 1;i--) propagate(l0 >> i);
        for(int i = log;i >= 1;i--) propagate((r0-1) >> i);

        T Lval = e(),Rval = e();
        while(l < r)
        {
            if(l & 1) Lval = op(Lval,node[l++]);
            if(r & 1) Rval = op(node[--r],Rval);

            l >>= 1;
            r >>= 1;
        }

        return op(Lval,Rval);
    }
};
