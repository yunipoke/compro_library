#include<vector>

vector<pair<long long,int>> primefactorize(long long n)
{
	vector<pair<long long,int>> ret;
	for(long long p = 2;p*p <= n;p++)
	{
		if(n%p == 0)
		{
			int e = 0;
			while(n%p == 0) n /= p,e++;

			ret.push_back(make_pair(p,e));
		}
	}

	if(n > 1) ret.push_back(make_pair(n,1));

	return ret;
}

