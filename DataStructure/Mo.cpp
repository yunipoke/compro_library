struct Mo{
    int sq;
    vector<int> left,right,order;

    Mo(int N,int Q)
    {
        order.resize(Q);
        sq = max<int>(1,1.0*N/ max<double>(1.0,sqrt(2.0*Q/3.0)));
        iota(order.begin(),order.end(),0);
    }

    void insert(int l,int r)
    {
        left.push_back(l);
        right.push_back(r);
    }

    template<class AL,class AR,class DL,class DR,class REM>
    void run(const AL &addleft,const AR &addright,const DL &delleft,const DR &delright,const REM &rem)
    {
        assert(left.size() == order.size());
        sort(order.begin(),order.end(),[&](int u,int v)
        {
            int ublock = left[u]/sq,vblock = left[v]/sq;
            if(ublock != vblock) return ublock < vblock;

            if(ublock & 1) return right[u] < right[v];
            return right[u] > right[v];
        });

        int nl = 0,nr = 0;
        for(int i:order)
        {
            while(nl > left[i]) addleft(--nl);
            while(nr < right[i]) addright(nr++);
            while(nl < left[i]) delleft(nl++);
            while(nr > right[i]) delright(--nr);

            rem(i);
        }
    }
};