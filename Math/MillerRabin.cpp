bool MillerRabin(long long N)
{
	if(N <= 1) return false;
	if(N == 2) return true;
	if(N % 2 == 0) return false;
	vector<long long> A;
	if(N < 4759123141LL)
	{
		A = {2,7,61};
	}
	else
	{
		A = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	}

	auto mult = [&N](long long x,long long y) -> long long
	{
		return (__int128_t) x * y % N;
	};

	auto mod_pow = [&mult](long long p,long long n) -> long long
	{
		long long res = 1;
		while(n)
		{
			if(n & 1) res = mult(res,p);
			n >>= 1;
			p = mult(p,p);
		}
		return res;
	};

	long long S = 0,D = N - 1;
	while(D % 2 == 0)
	{
		S++;
		D >>= 1;
	}

	for(const long long &a : A)
	{
		if(N <= a) return true;
		long long t;
		long long x = mod_pow(a,D);

		if(x == 1);
		else
		{
			for(t = 0;t < S;t++)
			{
				if(x == N - 1) break;
				x = mult(x,x); 
			}

			if(t == S) return false;
		}
	}

	return true;
}
