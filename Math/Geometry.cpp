namespace geometry
{
	using real = double;
	const real EPS = 1e-9;
	bool EQ(real a,real b)
	{
		return abs(a - b) < EPS;
	}

	struct Point
	{
		real x,y;

		Point(real x_ = 0,real y_ = 0) : x(x_),y(y_) {}

		Point operator-() const
		{
			return Point(-x,-y);
		}

		Point operator+(const Point &rhs) const
		{
			return Point(x + rhs.x,y + rhs.y);
		}

		Point operator-(const Point &rhs) const
		{
			return Point(x - rhs.x,y - rhs.y);
		}

		Point operator*(const real k) const
		{
			return Point(x * k,y * k);
		}

		Point operator/(const real k) const
		{
			assert(!EQ(0,k));
			return Point(x / k,y / k);
		}

		bool operator<(const Point &rhs) const
		{
			return EQ(x,rhs.x) ? y < rhs.y : x < rhs.x;
		}

		bool operator==(const Point &rhs) const
		{
			return EQ(x,rhs.x) && EQ(y,rhs.y);
		}
	};

	istream &operator>>(istream &is,Point &p)
	{
		return is >> p.x >> p.y;
	}

	ostream &operator<<(ostream &os,const Point &p)
	{
		return os << "(" << p.x << ", " << p.y << ")";
	}

	struct Line
	{
		Point p1,p2;
		Line(Point p1_ = Point(),Point p2_ = Point()) : p1(p1_),p2(p2_) {}
	};

	struct Segment : Line
	{
		Segment(Point p1_ = Point(),Point p2_ = Point()) : Line(p1_,p2_) {}
	};

	struct Circle
	{
		Point O;
		real r;
		Circle(Point O_ = Point(),real r_ = 0) : O(O_),r(r_) {}
	};

	using Polygon = vector<Point>;

	Point vec(const Line &l)
	{
		return l.p2 - l.p1;
	}
	real norm2(const Point &p)
	{
		return p.x * p.x + p.y * p.y;
	}
	real abs(const Point &p)
	{
		return hypot(p.x,p.y);
	}

	real dot(const Point &a,const Point &b)
	{
		return a.x * b.x + a.y * b.y;
	}
	
	real cross(const Point &a,const Point &b)
	{
		return a.x * b.y - a.y * b.x;
	}

	Point rotate(const Point &p,const real &theta)
	{
		return Point(p.x * cos(theta) - p.y * sin(theta), p.x * sin(theta) + p.y * cos(theta));
	}

	Point rotate(const Point &a,const Point &p,const real &theta)
	{
		Point q = rotate(p - a,theta);
		return a + q;
	}

	enum
	{
		ONLINE_FRONT = -2,
		CLOCKWISE= -1,
		ON_SEGMENT = 0,
		COUNTER_CLOCKWISE = 1,
		ONLINE_BACK = 2
	};

	int ccw(const Point &a,const Point &b)
	{
		real C = cross(a,b);
		return C > EPS ? COUNTER_CLOCKWISE : C < -EPS ? CLOCKWISE : dot(a,b) < -EPS ? ONLINE_BACK : norm2(b) - norm2(a) > EPS ? ONLINE_FRONT : ON_SEGMENT;
	}

	int ccw(const Point &a,const Point &b,const Point &c)
	{
		return ccw(b - a,c - a);
	}

	bool orthogonal(const Point &a,const Point &b)
	{
		return EQ(dot(a,b),0);
	}

	bool parallel(const Point &a,const Point &b)
	{
		return EQ(cross(a,b),0);
	}

	bool intersect(const Line &l,const Point &p)
	{
		return parallel(vec(l),p - l.p1);
	}

	bool intersect(const Segment &s,const Point &p)
	{
		return ccw(s.p1,s.p2,p) == ON_SEGMENT;
	}

	enum
	{
		OUT,
		ON,
		IN
	};

	int convex_contain(const Polygon &P,const Point &p)
	{
		if(P[0] == p)
		{
			return ON;
		}

		int L = 0,R = (int)P.size();
		while(R - L > 1)
		{
			int M = (L + R) / 2;
			if(ccw(P[0],P[M],p) == CLOCKWISE)
			{
				R = M;
			}
			else
			{
				L = M;
			}
		}
		
		if(R == 1)
		{
			return OUT;
		}
		
		if(L + 1 == (int)P.size())
		{
			if(intersect(Segment(P[0],P[L]),p))
			{
				return ON;
			}
			return OUT;
		}

		if(L == 1)
		{
			if(intersect(Segment(P[0],P[L]),p))
			{
				return ON;
			}
		}

		real tri = cross(P[L] - p,P[R] - p);
		return EQ(tri,0) ? ON : tri < -EPS ? OUT : IN;
	}
}; //namespace geometry
