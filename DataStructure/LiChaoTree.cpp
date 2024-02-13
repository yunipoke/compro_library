template<class T,T lower_limit,T upper_limit,T id>
struct LiChaoTree
{
	private:
	
	struct Line
	{
		T a,b;
		Line(T a,T b) : a(a),b(b) {}

		inline T eval(T x) const
		{
			return a * x + b;
		}
	};

	struct Node
	{
		Line x;
		Node *l, *r;

		Node(const Line &x) : x(x),l(nullptr),r(nullptr) {}
	};
	
	Node *root;

	Node *add_line(Node *node,Line &x,const T &lower,const T &upper,const T &lower_value,const T &upper_value)
	{
		if(!node)
		{
			return new Node(x);
		}

		T node_lower_value = node -> x.eval(lower);
		T node_upper_value = node -> x.eval(upper);

		if(node_lower_value <= lower_value && node_upper_value <= upper_value)
		{
			return node;
		}
		else if(node_lower_value >= lower_value && node_upper_value >= upper_value)
		{
			node -> x = x;
			return node;
		}
		else
		{
			T mid = (lower + upper) / 2;

			if(mid == upper)
			{
				mid--;
			}

			T node_mid_value = node -> x.eval(mid),mid_value = x.eval(mid);

			T nxt_lower_value = lower_value;
			T nxt_mid_value = mid_value;
			T nxt_upper_value = upper_value;

			if(node_mid_value > mid_value)
			{
				swap(node -> x,x);
				swap(node_lower_value,nxt_lower_value);
				swap(node_mid_value,nxt_mid_value);
				swap(node_upper_value,nxt_upper_value);
			}

			if(node_lower_value >= nxt_lower_value)
			{
				node -> l = add_line(node -> l,x,lower,mid,nxt_lower_value,nxt_mid_value);
			}
			else
			{
				node -> r = add_line(node -> r,x,mid + 1,upper,nxt_mid_value + x.a,nxt_upper_value);
			}

			return node;
		}
	}

	Node *add_segment(Node *node,Line &x,const T &x_l,const T &x_r,const T &lower,const T &upper,const T &lower_value,const T &upper_value)
	{
		if(upper < x_l || x_r < lower)
		{
			return node;
		}
		if(x_l <= lower && upper <= x_r)
		{
			Line y = x;
			return add_line(node,y,lower,upper,lower_value,upper_value);
		}

		if(node)
		{
			T node_lower_value = node -> x.eval(lower);
			T node_upper_value = node -> x.eval(upper);
			
			if(node_lower_value <= lower_value && node_upper_value <= upper_value)
			{
				return node;
			}
		}
		else
		{
			node = new Node(Line(0,id));
		}

		T mid = (lower + upper) / 2;
		if(mid == upper)
		{
			mid--;
		}

		T mid_value = x.eval(mid);
		node -> l = add_segment(node -> l,x,x_l,x_r,lower,mid,lower_value,mid_value);
		node -> r = add_segment(node -> r,x,x_l,x_r,mid + 1,upper,mid_value + x.a,upper_value);
		return node;
	}

	T query(const Node *node,const T &x_l,const T &x_r,const T &x) const
	{
		if(!node)
		{
			return id;
		}

		T res = node -> x.eval(x);

		if(x_l == x_r)
		{
			return res;
		}

		T x_m = (x_l + x_r) / 2;
		if(x_m == x_r)
		{
			x_m--;
		}
		if(x <= x_m)
		{
			res = min(res,query(node -> l,x_l,x_m,x));
		}
		else
		{
			res = min(res,query(node -> r,x_m + 1,x_r,x));
		}
		return res;
	}

	public:

	LiChaoTree() : root(nullptr) {}
	
	void add_line(const T &a,const T &b)
	{
		Line x(a,b);
		root = add_line(root,x,lower_limit,upper_limit,x.eval(lower_limit),x.eval(upper_limit));
	}

	//[l,r)
	void add_segment(const T &l,const T &r,const T &a,const T &b)
	{
		Line x(a,b);
		root = add_segment(root,x,l,r - 1,lower_limit,upper_limit,x.eval(lower_limit),x.eval(upper_limit));
	}

	T query(const T &x) const
	{
		assert(lower_limit <= x && x <= upper_limit);
		return query(root,lower_limit,upper_limit,x);
	}
};
