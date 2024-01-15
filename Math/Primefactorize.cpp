vector<pair<long long,int>> PrimeFactorize(long long N)
{
	vector<pair<long long,int>> res;
	for(long long p = 2;p * p <= N;p++)
	{
		res.push_back(make_pair(p,0));
		while(N % p == 0)
		{
			N /= p;
			res.back().second++;
		}
	}
	
	if(N > 1)
	{
		res.push_back(make_pair(N,1));
	}

	return res;
}
