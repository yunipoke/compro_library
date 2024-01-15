template<class T> struct Matrix
{
	private:
	vector<vector<T>> M;
	int H,W;

	public:
	static const Matrix e(int N)
	{
		Matrix ret(N,N);
		for(int i = 0;i < N;i++) ret[i][i] = 1;
		return ret;
	};
	constexpr Matrix(int h,int w,T x = 0) noexcept
	{
		H = h,W = w;
		M.assign(H,vector<T>(W,x));
	}

	constexpr vector<T> &operator[](const int i) noexcept
	{
		assert(0 <= i && i < H);
		return M[i];
	}

	constexpr vector<T> operator[](const int i) const
	{
		assert(0 <= i && i < H);
		return M[i];
	}

	constexpr Matrix &operator*=(const Matrix &rhs) noexcept
	{
		assert(W == rhs.H);
		Matrix tmp(H,rhs.W);
		for(int i = 0;i < H;i++)
		{
			for(int j = 0;j < rhs.W;j++)
			{
				for(int k = 0;k < W;k++)
				{
					tmp[i][j] += M[i][k] * rhs.M[k][j];
				}
			}
		}
		swap(*this,tmp);
		return *this;
	}

	constexpr Matrix power(long long N) noexcept
	{
		assert(H == W);
		assert(N >= 0);
		Matrix res = e(H),P = *this;
		while(N)
		{
			if(N & 1) res *= P;
			P *= P;
			N >>= 1;
		}
		return res;
	};

	friend Matrix operator*(const Matrix &lhs,const Matrix &rhs)
	{
		return Matrix(lhs) *= rhs;
	}

	friend ostream &operator<<(ostream &os,const Matrix &x)
	{
		for(int i = 0;i < x.H;i++)
		{
			for(int j = 0;j < x.W;j++)
			{
				os << x.M[i][j] << (i + 1 < x.H && j + 1 == x.W ? "\n":" ");
			}
		}
		return os;
	}
};
/* using mat = Matrix<mint>; */
