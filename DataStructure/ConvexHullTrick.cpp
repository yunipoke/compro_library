template<class T = long long> struct ConvexHullTrick
{
	private:
	bool minflag;
	static const T Q = numeric_limits<T>::lowest();
	struct Line
	{
		T a,b;
		mutable function<const Line*()> NEX;
		bool operator<(const Line &other) const
		{
			if(b == Q)
			{
				const Line* nl = NEX();
				if(!nl) return true;
				return (nl -> a - other.a) * a + (nl -> b - other.b) < 0;
			}
			else if(other.b == Q)
			{
				const Line* nl = NEX();
				if(!nl) return false;
				return (nl -> a - a) * other.a + (nl -> b - b) > 0;
			}
			else return a < other.a;
		}
	};
	bool isNotNeeded(const typename set<Line>::iterator it)
	{
		const auto nt = next(it);
		if(it == Lines.begin())
		{
			if(nt == Lines.end()) return false;
			return (*it).a == (*nt).a && (*it).b <= (*nt).b;
		}
		else
		{
			const auto pt = prev(it);
			if(nt == Lines.end()) return (*it).a == (*pt).a && (*it).b <= (*pt).b;
			else return ((*pt).b-(*it).b) * ((*nt).a-(*it).a) >= ((*nt).b-(*it).b) * ((*pt).a-(*it).a);
		}
	}
	multiset<Line> Lines;

	public:
	constexpr ConvexHullTrick(bool minflag = true) : minflag(minflag) {}

	constexpr void add(T a,T b) noexcept
	{
		if(minflag) a = -a,b = -b;
		auto it = Lines.insert(Line{a,b});
		(*it).NEX = [=] {return next(it) == Lines.end() ? nullptr : &*next(it);};
		if(isNotNeeded(it)) Lines.erase(it);
		else
		{
			while(next(it) != Lines.end() && isNotNeeded(next(it))) Lines.erase(next(it));
			while(it != Lines.begin() && isNotNeeded(prev(it))) Lines.erase(prev(it));
		}
	}

	constexpr T get(T x) noexcept
	{
		Line l = *Lines.lower_bound(Line{x,Q});
		T res = l.a * x + l.b;
		if(minflag) res = -res;
		return res;
	}
};
