using ull = unsigned long long;
const ull mod = (1ull << 61) - 1;
ull mul(ull a,ull b)
{
	ull au = a >> 31;
	ull ad = a & ((1UL << 31)-1);
	ull bu = b >> 31;
	ull bd = b & ((1UL << 31)-1);
	ull mid = au*bd + bu*ad;
	ull midu = mid >> 30;
	ull midd = mid & ((1UL << 30)-1);

	ull res = au*bu*2 + midu + (midd << 31) + ad*bd;

	res = (res >> 61) + (res & mod);
	if(res >= mod) res -= mod;

	return res;
}
mt19937_64 mt{(unsigned int)time(nullptr)};
