struct modint
{
	private:
	unsigned int value;
	static int &mod()
	{
		static int m = 0;
		return m;
	}

	public:
	static void setmod(const int m)
	{
		mod() = m;
	}
	modint(const long long x = 0) noexcept
	{
		long long y = x;
		if(y < 0 || y >= mod())
		{
			y %= mod();
			if(y < 0) y += mod();
		}
		value = (unsigned int)y;
	}
	unsigned int val() noexcept {return value;}
	modint &operator+=(const modint &other) noexcept
	{
		value += other.value;
		if(value >= mod()) value -= mod();
		return *this;
	}
	modint &operator-=(const modint &other) noexcept
	{
		unsigned int x = value;
		if(x < other.value) x += mod();
		x -= other.value;
		value = x;
		return *this;
	}
	modint &operator*=(const modint &other) noexcept
	{
		unsigned long long x = value;
		x *= other.value;
		value = (unsigned int) (x % mod());
		return *this;
	}
	modint &operator/=(const modint &other) noexcept
	{
		return *this *= other.inverse();
	}
	modint inverse() const noexcept
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
	modint power(long long N) const noexcept
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
	modint operator+() {return *this;}
	modint operator-() {return modint() - *this;}
	modint &operator++(int) noexcept {return *this += 1;}
	modint &operator--(int) noexcept {return *this -= 1;}
	friend modint operator+(const modint& lhs, const modint& rhs) {return modint(lhs) += rhs;}
	friend modint operator-(const modint& lhs, const modint& rhs) {return modint(lhs) -= rhs;}
	friend modint operator*(const modint& lhs, const modint& rhs) {return modint(lhs) *= rhs;}
	friend modint operator/(const modint& lhs, const modint& rhs) {return modint(lhs) /= rhs;}
	friend ostream &operator<<(ostream &os,const modint &x) {return os << x.value;}
};
using mint = modint;
