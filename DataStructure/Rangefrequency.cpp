template<class S>
struct RangeFreq
{
	private:
	int size,N;
	vector<vector<S>> node;

	public:
	RangeFreq(const vector<S> &A)
	{
		size = 1;
		N = (int)A.size();
		while(size < N) size <<= 1;

		node.assign(2*size,{});
		for(int i = 0;i < N;i++) node[i+size] = {A[i]};
		for(int i = size-1;i > 0;i--) merge(node[2*i].begin(),node[2*i].end(),node[2*i+1].begin(),node[2*i+1].end(),back_inserter(node[i]));
	}

	int query(int l,int r,S x)
	{
		assert(0 <= l && l <= r && r <= size);
		int L = 0,R = 0;
		l += size,r += size;

		while(l < r)
		{
			if(l & 1)
			{
				L += node[l].end()-lower_bound(node[l].begin(),node[l].end(),x);
				l++;
			}

			if(r & 1)
			{
				r--;
				R += node[r].end()-lower_bound(node[r].begin(),node[r].end(),x);
			}
			l >>= 1,r >>= 1;
		}

		return L+R;
	}

	int query(int l,int r,S x,S y)
	{
		assert(x <= y);
		return query(l,r,x) - query(l,r,y);
	}
};
