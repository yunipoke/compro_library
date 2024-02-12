#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <cmath>
using namespace std;

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
		return os << p.x << " " << p.y;
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
	
	bool orthogonal(const Line &a,const Line &b)
	{
		return orthogonal(vec(a),vec(b));
	}

	bool parallel(const Point &a,const Point &b)
	{
		return EQ(cross(a,b),0);
	}

	bool parallel(const Line &a,const Line &b)
	{
		return parallel(vec(a),vec(b));
	}

	bool intersect(const Line &l,const Point &p)
	{
		return parallel(vec(l),p - l.p1);
	}

	bool intersect(const Segment &s,const Point &p)
	{
		return ccw(s.p1,s.p2,p) == ON_SEGMENT;
	}

	bool intersect(const Segment &a,const Segment &b)
	{
		return ccw(a.p1,a.p2,b.p1) * ccw(a.p1,a.p2,b.p2) <= 0 && ccw(b.p1,b.p2,a.p1) * ccw(b.p1,b.p2,a.p2) <= 0;
	}

	Point cross_point(const Line &a,const Line &b)
	{
		real s1 = cross(vec(a),b.p1 - a.p1);
		real s2 = -cross(vec(a),b.p2 - a.p1);
		return b.p1 + vec(b) * (s1 / (s1 + s2));
	}

	enum
	{
		OUT,
		ON,
		IN
	};

	Polygon convex_hull(Polygon P,bool ONLINE = false,bool SORT = false)
	{
		if((int)P.size() <= 2)
		{
			return P;
		}
		sort(P.begin(),P.end());
		Polygon res(2 * P.size());
		int sz = 0;
		real threshold = EPS;
		if(ONLINE)
		{
			threshold = -EPS;
		}

		for(int i = 0;i < (int)P.size();i++)
		{
			while(sz >= 2 && cross(res[sz - 1] - res[sz - 2],P[i] - res[sz - 1]) < threshold)
			{
				sz--;
			}
			res[sz++] = P[i];
		}
		for(int i = (int)P.size() - 2,t = sz + 1;i >= 0;i--)
		{
			while(sz >= t && cross(res[sz - 1] - res[sz - 2],P[i] - res[sz - 1]) < threshold)
			{
				sz--;
			}
			res[sz++] = P[i];
		}
		res.resize(sz - 1);
		if(SORT)
		{
			int mi = 0;
			for(int i = 1;i < (int)res.size();i++)
			{
				if((EQ(res[mi].y,res[i].y) && res[mi].x > res[i].x) || res[mi].y > res[i].y)
				{
					mi = i;
				}
			}
			rotate(res.begin(),res.begin() + mi,res.end());
		}
		return res;
	}

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
