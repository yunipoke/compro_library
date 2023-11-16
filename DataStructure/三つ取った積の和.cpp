#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

int n;
int a[200];
long s[210];
long p[210];
long dp[210][4];

long solve1()
{
    long res = 0;
    for(int i = 0;i < n;i++)for(int j = i+1;j < n;j++)for(int k = j+1;k < n;k++) res += a[i]*a[j]*a[k];

    return res;
}

long solve2()
{
    long res = 0;
    for(int i = 0;i < n;i++) res += a[i]*p[i];
    return res;
}

long solve3()
{
    for(int i = 0;i < n;i++) dp[i+1][1] = a[i];

    for(int i = 0;i < n;i++)for(int j = 1;j <= 3;j++)
    {
        dp[i+1][j] += dp[i][j];
        if(j < 3) dp[i+1][j+1] += a[i]*dp[i][j];
    }

    for(int i = 0;i <= n;i++)for(int j = 0;j <= 3;j++) cout << dp[i][j] << (j==3 ? "\n":" ");

    return dp[n][3];
}

int main()
{
    cin >> n;
    for(int i = 0;i < n;i++) cin >> a[i],s[i+1] = s[i] + a[i];
    for(int i = n-3;i >= 0;i--) p[i] = p[i+1] + a[i+1]*(s[n]-s[i+2]);

    cout << n << endl;
    for(int i = 0;i < n;i++) cout << a[i] << (i+1 == n ? "\n":" ");
    cout << "\n";

    long x = solve1();
    long y = solve2();
    long z = solve3();

    if(x == y && y == z) cout << "AC" << endl;
    else cout << "WA" << " " << x << " " << y << " " << z << endl;
}
