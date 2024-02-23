template<class T = long long>
T Extgcd(T a,T b,T &x,T &y)
{
	x = 1,y = 0;
	T p = 0,q = 1;
	while(b)
	{
		T t = a / b;
		a -= t * b; swap(a,b);
		x -= t * p; swap(x,p);
		y -= t * q; swap(y,q);
	}
	return a;
}
