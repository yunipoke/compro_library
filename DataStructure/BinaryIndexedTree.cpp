template<class T> struct BIT
{
	private:
	int N;
	vector<T> node;

	public:

	BIT() : N(0) {}
	BIT(int N) : N(N), node(N) {}

	void add(int pos,T x)
	{
		assert(0 <= pos && pos < N);
		pos++;
		while(pos <= N)
		{
			node[pos-1] += x;
			pos += pos & -pos;
		}
	}

	T sum(int l,int r)
	{
		assert(0 <= l && l <= N && r <= N);
		return sum(r) - sum(l);
	}

	T sum(int r)
	{
		T ret = 0;
		while(r > 0)
		{
			ret += node[r-1];
			r -= r & -r;
		}
		return ret;
	}

	T sum() {return sum(N);}
	
};
