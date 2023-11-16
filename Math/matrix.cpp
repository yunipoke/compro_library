
template<class T> struct mat
{
    private:
    vector<vector<T>> m;
    int h,w;

    public:
    constexpr mat(int _h,int _w,T x = 0) noexcept {m.assign(_h,vector<T>(_w,x));h = _h,w = _w;}

    constexpr vector<T> operator[](const int i) const {assert(0 <= i && i < h); return m[i];}

    constexpr vector<T> &operator[](const int i) noexcept {assert(0 <= i && i < h); return m[i];}

    constexpr mat operator+(mat &other) noexcept
    {
        mat tmp = *this;
        return tmp += other;
    }

    constexpr mat operator-(mat &other) noexcept
    {
        mat tmp = *this;
        return tmp -= other;
    }

    constexpr mat operator*(mat &other) noexcept
    {
        mat tmp = *this;
        return tmp *= other;
    }

    constexpr mat &operator+=(mat &other) noexcept
    {
        assert(h == other.h && w == other.w);

        for(int i = 0;i < h;i++)for(int j = 0;j < w;j++) m[i][j] += other[i][j];

        return *this;
    }

    constexpr mat &operator-=(mat &other) noexcept
    {
        assert(h == other.h && w == other.w);

        for(int i = 0;i < h;i++)for(int j = 0;j < w;j++) m[i][j] -= other[i][j];

        return *this;
    }

    constexpr mat &operator*=(mat &other) noexcept
    {
        assert(w == other.h);
        mat tmp(h,other.w);
        for(int i = 0;i < h;i++)for(int j = 0;j < other.w;j++)for(int k = 0;k < w;k++) tmp[i][j] += m[i][k]*other[k][j];

        for(int i = 0;i < h;i++)
        {
            m[i].resize(other.w);
            for(int j = 0;j < other.w;j++) m[i][j] = tmp[i][j];
        }

        return *this;
    }

    constexpr mat power(long n) noexcept
    {
        assert(h == w);
        assert(n >= 0);
        mat res(h,w);
        for(int i = 0;i < h;i++) res[i][i] = 1;

        mat p = *this;
        long ex = n;

        while(ex)
        {
            if(ex & 1) res *= p;
            p *= p;
            ex >>= 1;
        }

        return res;
    }

    constexpr bool operator==(mat &other) noexcept
    {
        assert(h == other.h && w == other.w);
        bool res = true;
        for(int i = 0;i < h;i++)for(int j = 0;j < w;j++) if(m[i][j] != other[i][j]) res = false;

        return res;
    }

    constexpr bool operator!=(mat &other) noexcept
    {
        assert(h == other.h && w == other.w);
        bool res = false;
        for(int i = 0;i < h;i++)for(int j = 0;j < w;j++) if(m[i][j] != other[i][j]) res = true;

        return res;
    }

    template<class S> friend ostream &operator<<(ostream &os,const mat<S> &x);
};

template<class S> ostream &operator<<(ostream &os,const mat<S> &x)
{
    for(int i = 0;i < x.h;i++)for(int j = 0;j < x.w;j++)
    {
        os << x[i][j] << (j+1 == x.w && i+1 < x.h ? "\n":" ");
        return os;
    }
}