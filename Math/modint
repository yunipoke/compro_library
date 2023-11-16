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

