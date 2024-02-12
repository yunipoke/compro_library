long long floor_sum(long long N,long long M,long long A,long long B)
{
	long long res = 0;
	if(A >= M)
	{
		res += N * (N - 1) / 2 * (A / M);
		A %= M;
	}
	
	if(B >= M)
	{
		res += N * (B / M);
		B %= M;
	}

	long long F = A * (N - 1) + B;
	if(F >= M)
	{
		long long Q = F / M;
		long long R = F % M;
		res += Q + floor_sum(Q,A,M,R);
	}
	return res;
}
