template<int m> struct modint
{
	private:
	unsigned int value;
	static constexpr int mod() {return m;}

	public:
	constexpr modint(const long long x = 0) noexcept
	{
		long long y = x;
		if(y < 0 || y >= mod())
		{
			y %= mod();
			if(y < 0) y += mod();
		}
		value = (unsigned int)y;
	}
	constexpr unsigned int val() noexcept {return value;}
	constexpr modint &operator+=(const modint &other) noexcept
	{
		value += other.value;
		if(value >= mod()) value -= mod();
		return *this;
	}
	constexpr modint &operator-=(const modint &other) noexcept
	{
		unsigned int x = value;
		if(x < other.value) x += mod();
		x -= other.value;
		value = x;
		return *this;
	}
	constexpr modint &operator*=(const modint &other) noexcept
	{
		unsigned long long x = value;
		x *= other.value;
		value = (unsigned int) (x % mod());
		return *this;
	}
	constexpr modint &operator/=(const modint &other) noexcept
	{
		return *this *= other.inverse();
	}
	constexpr modint inverse() const noexcept
	{
		assert(value);
		long long a = value,b = mod(),x = 1,y = 0;
		while(b)
		{
			long long q = a/b;
			a -= q*b; swap(a,b);
			x -= q*y; swap(x,y);
		}
		return modint(x);
	}
	constexpr modint power(long long N) const noexcept
	{
		assert(N >= 0);
		modint p = *this,ret = 1;
		while(N)
		{
			if(N & 1) ret *= p;
			p *= p;
			N >>= 1;
		}
		return ret;
	}
	constexpr modint operator+() {return *this;}
	constexpr modint operator-() {return modint() - *this;}
	constexpr modint &operator++(int) noexcept {return *this += 1;}
	constexpr modint &operator--(int) noexcept {return *this -= 1;}
	friend modint operator+(const modint& lhs, const modint& rhs) {return modint(lhs) += rhs;}
	friend modint operator-(const modint& lhs, const modint& rhs) {return modint(lhs) -= rhs;}
	friend modint operator*(const modint& lhs, const modint& rhs) {return modint(lhs) *= rhs;}
	friend modint operator/(const modint& lhs, const modint& rhs) {return modint(lhs) /= rhs;}
	friend ostream &operator<<(ostream &os,const modint &x) {return os << x.value;}
};
/* using mint = modint<998244353>; */
/* using mint = modint<1000000007>; */

template<class S>
struct combination
{
	private:
	vector<S> f,invf;

	public:
	combination(int N = 0) : f(1,1),invf(1,1)
	{
		update(N);
	}

	void update(int N)
	{
		if((int)f.size() > N) return;
		int pi = (int)f.size();
		N = max(N,pi*2);

		f.resize(N+1),invf.resize(N+1);

		for(int i = pi;i <= N;i++) f[i] = f[i-1]*i;
		invf[N] = S(1)/f[N];
		for(int i = N-1;i >= pi;i--) invf[i] = invf[i+1]*(i+1);
	}

	S factorial(int N)
	{
		update(N);
		return f[N];
	}

	S invfactorial(int N)
	{
		update(N);
		return invf[N];
	}

	S P(int N,int K)
	{
		assert(0 <= K && K <= N);
		update(N);
		return f[N]*invf[N-K];
	}

	S C(int N,int K)
	{
		assert(0 <= K && K <= N);
		update(N);
		return f[N]*invf[K]*invf[N-K];
	}
};
combination<mint> C;
