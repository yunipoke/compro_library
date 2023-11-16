#include<iostream>
#include<cassert>
using namespace std;

const int p[9] = {4,9,5,7,11,13,17,19,23};
int head[9],b[110],rest[9], out[110];
const int m = 108;

long extgcd(long a,long b,long &x,long &y){

    if(b == 0){
        x = 1;y = 0;
        return a;
    }

    long q = a/b;
    long g = extgcd(b,a-q*b,x,y);
    long z = x-q*y;
    x = y,y = z;
    return g;
}

int main()
{
    cout << m << endl;
    int s = 0;

    for(int i = 0;i < 9;i++)
    {
        for(int j = 1;j <= p[i];j++)
        {
            int a = j + 1;
            if(a > p[i]) a %= p[i];
            a += s;
            cout << a << (i+1 == 9 && j == p[i] ? "":" ");
            if(j == p[i]) head[i] = a + 1;
            out[j+s] = a;
        }

        s += p[i];
    }

    cout << endl;

    cout << flush;

    int now = 1;
    int j = 0;
    for(int i = 1;i <= m;i++)
    {
        cin >> b[i];
        if(i == now)
        {
            rest[j] = (b[i] - i + 2*p[j])%p[j];
            now += p[j++];
        }
    }

    long long n = 0,M = 1;

    for(int i = 0;i < 9;i++)
    {
        long x,y;
        long g = extgcd(M,p[i],x,y);
        long tmp = (rest[i]-n)/g*x%(p[i]/g);

        // Mx+py = 1
        // ans%M = n; ans%p = rest;
        // py % M = 1; Mx % p = 1;
        // ans %Mp = Mx * rest + py * n;
        // tmp = (rest-n)x%p
        // n + Mtmp = n + M(rest-n)x%p
        // (n + M(rest-n)x%p)%p == rest && (n + M(rest-n)x%p)%M == n;

        n += M*tmp;
        M *= p[i]/g;
    }

    if(n < 0) n += M;

    cout << n << endl;
    cout << flush;
}