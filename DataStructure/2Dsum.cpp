#include<iostream>
#include<cassert>
using namespace std;

int h,w;
long a[3100][3100],s[3100][3100];

int main()
{
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    cin >> h >> w;
    for(int i = 0;i < h;i++)for(int j = 0;j < w;j++) cin >> a[i][j];

    for(int i = 0;i < h;i++)for(int j = 0;j < w;j++) s[i+1][j+1] = s[i+1][j] + a[i][j];
    for(int j = 0;j < w;j++)for(int i = 0;i < h;i++) s[i+1][j+1] += s[i][j+1];
    // s[ni][nj] - s[ni][j] - s[i][nj] + s[i][j] で[i,ni),[j,nj) の和を取得
}