int ceil_log2(int n)
{
	int res = 0;
	while((1U << res) < (unsigned int)n)
	{
		res++;
	}
	return res;
}

template<class mint> void Butterfly(vector<mint> &a,bool inverse = false)
{
	int N = (int)a.size();
	int H = __builtin_ctz(N);
	assert(N == (1 << H));

	static constexpr int pr = mint::primitive_root();
	static bool first_call = true;
	static vector<mint> w(30),iw(30);
	if(first_call)
	{
		first_call = false;
		int cnt = __builtin_ctz(mint::get_mod() - 1);
		mint e = mint(pr).power((mint::get_mod() - 1) >> cnt);
		mint ie = e.inverse();
		for(int i = cnt;i >= 1;i--)
		{
			w[i] = e;
			iw[i] = ie;
			e *= e;
			ie *= ie;
		}
	}

	for(int i = 0;i < N;i++)
	{
		int rev = 0;
		int cur = i;
		for(int j = 0;j < H;j++)
		{
			rev = (rev << 1) | (cur & 1);
			cur >>= 1;
		}
		if(rev > i)
		{
			swap(a[i],a[rev]);
		}
	}

	int width = 2,offset = 1;
	int log = 1;
	while(width <= N)
	{
		mint cur = inverse ? iw[log] : w[log];

		for(int i = 0;i < N;i += width)
		{
			mint root = 1;
			for(int j = i;j < i + offset;j++)
			{
				mint s = a[j],t = a[j + offset];
				a[j] = s + t * root;
				a[j + offset] = s - t * root;
				root *= cur;
			}
		}
		width <<= 1;
		offset <<= 1;
		log++;
	}
}

template<class mint> vector<mint> Convolution(vector<mint> a,vector<mint> b)
{
	int N = (int)a.size(),M = (int)b.size();
	int L = 1 << ceil_log2(N + M - 1);

	a.resize(L);
	b.resize(L);

	Butterfly(a);
	Butterfly(b);
	for(int i = 0;i < L;i++)
	{
		a[i] *= b[i];
	}
	Butterfly(a,true);
	a.resize(N + M - 1);
	const mint invL = mint(L).inverse();
	for(int i = 0;i < N + M - 1;i++)
	{
		a[i] *= invL;
	}
	return a;
}
