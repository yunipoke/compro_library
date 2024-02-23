template<class T = long long>
T gcd(T a,T b)
{
	while(b)
	{
		a %= b;
		swap(a,b);
	}
	return a;
}

template<class T = long long>
T lcm(T a,T b)
{
	return a / gcd<T>(a,b) * b;
}
