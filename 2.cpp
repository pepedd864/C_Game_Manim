#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 20;

int n;
char g[N][N];               //存图
bool col[N], dg[N], udg[N]; //点对应的横竖两个斜线上是否有皇后

void dfs(int u)
{
  for (int i = 0; i < n; i++)                     //第r行,第i列是否放皇后
    if (!col[i] && !dg[u + i] && !udg[n - u + i]) //不冲突，才能放皇后
    {
      g[u][i] = 'Q';
      col[i] = dg[u + i] = udg[n - u + i] = true;  //标记，如果放了皇后就写true,避免在这一层重复搜索
      dfs(u + 1);                                  //处理下一层
      col[i] = dg[u + i] = udg[n - u + i] = false; //回溯的过程,恢复现场
      g[u][i] = '.';                               //
    }
  if (u == n) //当棋子用完的时候
  {
    for (int i = 0; i < n; i++)
      puts(g[i]);
    puts("");
    return;
  }
}
int main()
{
  cin >> n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      g[i][j] = '.';
  dfs(0); //由棋子的数量来搜索
  return 0;
}