
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

	if(!inverse)
	{
		int width = N;
		int log = H;
		const mint im = w[2];
		while(width > 1)
		{
			mint cur = w[log];

			if(width == 2)
			{
				int offset = width >> 1;
				for(int i = 0;i < N;i += width)
				{
					mint root = 1;
					for(int j = i;j < i + offset;j++)
					{
						mint s = a[j],t = a[j + offset];
						a[j] = s + t;
						a[j + offset] = (s - t) * root;
						root *= cur;
					}
				}
				width >>= 1;
				log--;
			}
			else
			{
				int offset = width >> 2;
				for(int i = 0;i < N;i += width)
				{
					mint root = 1;
					for(int j = i;j < i + offset;j++)
					{
						mint root2 = root * root;
						mint root3 = root2 * root;
						mint s = a[j],t = a[j + offset],u = a[j + offset * 2],v = a[j + offset * 3];
						mint spu = s + u;
						mint smu = s - u;
						mint tpv = t + v;
						mint tmvim = (t - v) * im;
						a[j] = spu + tpv;
						a[j + offset] = (spu - tpv) * root2;
						a[j + offset * 2] = (smu + tmvim) * root;
						a[j + offset * 3] = (smu - tmvim) * root3;
						root *= cur;
					}
				}
				width >>= 2;
				log -= 2;
			}

		}
	}
	else
	{
		int width = H & 1 ? 2 : 4;
		int log = H & 1 ? 1 : 2;
		const mint im = iw[2];
		while(width <= N)
		{
			mint cur = iw[log];

			if(width == 2)
			{
				int offset = width >> 1;
				for(int i = 0;i < N;i += width)
				{
					mint root = 1;
					for(int j = i;j < i + offset;j++)
					{
						mint s = a[j],t = a[j + offset] * root;
						a[j] = s + t;
						a[j + offset] = s - t;
						root *= cur;
					}
				}
			}
			else
			{
				int offset = width >> 2;
				for(int i = 0;i < N;i += width)
				{
					mint root = 1;
					for(int j = i;j < i + offset;j++)
					{
						mint root2 = root * root;
						mint root3 = root2 * root;
						mint s = a[j],t = a[j + offset] * root2,u = a[j + offset * 2] * root,v = a[j + offset * 3] * root3;
						mint spt = s + t;
						mint smt = s - t;
						mint upv = u + v;
						mint umvim = (u - v) * im;
						a[j] = spt + upv;
						a[j + offset] = smt + umvim;
						a[j + offset * 2] = spt - upv;
						a[j + offset * 3] = smt - umvim;
						root *= cur;
					}
				}
			}

			width <<= 2;
			log += 2;
		}
	}
}

template<class mint> vector<mint> Convolution(vector<mint> a,vector<mint> b)
{
	int N = (int)a.size(),M = (int)b.size();

	if(min(N,M) <= 60)
	{
		vector<mint> res(N + M - 1);
		if(N < M)
		{
			swap(N,M);
			swap(a,b);
		}
		for(int i = 0;i < N;i++)
		{
			for(int j = 0;j < M;j++)
			{
				res[i + j] += a[i] * b[j];
			}
		}
		return res;
	}

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
