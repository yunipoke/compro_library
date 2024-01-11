template<class T,T (*op)(T,T),T (*e)()> struct segtree
{
	private:
	int size,N;
	vector<T> node;

	public:
	segtree(int N = 0) : segtree(vector<T>(N,e())) {}
	segtree(const vector<T> &V)
	{
		N = (int)V.size();
		size = 1;
		while(size < N) size <<= 1;
		node.assign(2*size,e());
		for(int i = 0;i < N;i++) node[i+size] = V[i];
		for(int i = size-1;i >= 1;i--) node[i] = op(node[i*2],node[i*2+1]);
	}
	void replace(int pos,T x) {func_update(pos,x,[](T u,T v){return u = v;});}
	void add(int pos,T x) {func_update(pos,x,[](T u,T v){return u + v;});}
	void func_update(int pos,T x) {func_update(pos,x,op);}
	void func_update(int pos,T x,T (*func)(T,T))
	{
		assert(0 <= pos && pos < N);
		pos += size;
		node[pos] = func(node[pos],x);
		pos >>= 1;
		while(pos)
		{
			node[pos] = op(node[pos*2],node[pos*2+1]);
			pos >>= 1;
		}
	}
	T operator[](int pos)
	{
		assert(0 <= pos && pos < N);
		return node[pos+size];
	}
	T prod(int l,int r)
	{
		assert(0 <= l && l <= r && r <= N);
		T L = e(),R = e();
		l += size,r += size;
		while(l < r)
		{
			if(l & 1) L = op(L,node[l++]);
			if(r & 1) R = op(node[--r],R);
			l >>= 1,r >>= 1;
		}
		return op(L,R);
	}
	T prod() {return node[1];}

	template<class F> int max_right(int l,F f)
	{
		assert(0 <= l && l <= N);
		assert(f(e()));
		if(l == N) return N;
		l += size;
		T val = e();
		do
		{
			while(!(l & 1)) l >>= 1;
			if(!f(op(val,node[l])))
			{
				while(l < size)
				{
					l <<= 1;
					if(f(op(val,node[l]))) val = op(val,node[l++]);
				}
				return l - size;
			}
			val = op(val,node[l++]);
		} while((l & -l) != l);
		return N;
	}

	template<class F> int min_left(int r,F f)
	{
		assert(0 <= r && r <= N);
		assert(f(e()));
		if(r == 0) return 0;
		r += size;
		T val = e();
		do
		{
			r--;
			while(r > 1 && (r & 1)) r >>= 1;
			if(!f(op(node[r],val)))
			{
				while(r < size)
				{
					r <<= 1;
					r++;
					if(f(op(node[r],val))) val = op(node[r--],val);
				}
				return r + 1 - size;
			}
			val = op(node[r],val);
		} while((r & -r) != r);
		return 0;
	}
};
