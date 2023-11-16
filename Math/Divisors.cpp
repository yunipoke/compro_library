#include<vector>
#include<algorithm>
vector<long long> divisors(long long n)
{
	vector<long long> ret;
	for(long long i = 1;i*i <= n;i++)
	{
		if(n%i == 0)
		{
			ret.push_back(i);
			if(i != n/i) ret.push_back(n/i);
		}
	}

	sort(ret.begin(),ret.end());

	return ret;
}
