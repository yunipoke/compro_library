vector<long long> Divisors(long long N)
{
	vector<long long> res;
	for(long long i = 1;i * i <= N;i++)
	{
		if(N % i == 0)
		{
			res.push_back(i);
			if(i != N / i) res.push_back(N / i);
		}
	}

	sort(res.begin(),res.end());

	return res;
}
