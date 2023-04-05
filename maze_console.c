#include <windows.h>
#include <conio.h>
#include <stdio.h>

#define Len 21 // 地图长度, 为奇数, 否则墙壁缺失
// 背景颜色
#define RED 64
#define BLUE 48
#define BLACK 0
#define GREEN 32
#define YELLOW 96

int c, i;                                             // i循环变量
int place = Len;                                      // 玩家的位置
int map[Len * Len] = {0};                             // 地图 , 1是路，0是墙
int move[8] = {-1, 1, -Len, Len, 'a', 'd', 'w', 's'}; // 存储了移动方向和读入方向

void color(short x, short y)
{
  /*字体颜色
    * 15 #亮白色 	14 #淡黄色 		13 #淡紫色
    * 12 #淡红色 	11 #淡浅绿色 	10 #淡绿色
    * 9  #淡蓝色	8  #灰色		7  #白色
    * 6  #黄色		5  #紫色		4  #红色
    * 3  #浅绿色	2  #绿色		1  #蓝色
    * #背景颜色 *16
    */
  if (x >= 0 && x <= 15) //参数在0-15的范围颜色
                         //只有一个参数时，改变字体颜色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x | y);
  else //默认的颜色白色
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void dig(int v)
{
  // v 是地图的索引，是dfs的关键
  // 这里的数组是关键点，利用了隔行遍历的思想，就可以创造一条条联通的路
  // 通常的思路是四面墙，两两联通形成路
  int a[4] = {2, -2, 2 * Len, -2 * Len}; // 方向数组，右、左、下、上
  int i, j;                              // 初始化循环变量
  // 随机方向, 即重新洗牌, 让下面的遍历每次得到不一样的结果
  for (i = 0; j = rand() % 4, i < 4; i++)
  {
    if (i != j)
    {
      // 异或运算 交换变量(a[i] <=> a[j])
      a[i] ^= a[j];
      a[j] ^= a[i];
      a[i] ^= a[j];
    }
  }
  for (map[v] = 1, i = 0; i < 4; i++)
  {
    // 判断下一个方向是否越界或者是否是路(已遍历过)，就重新选择方向
    if (v + a[i] < 0 || v + a[i] > Len * Len || map[v + a[i]])
      continue;
    // a[i] == 2 || a[i] == -2 是向左向右移动，后面的表示纵向距离等于1，即下个方向在下一行，而移动方向是左右方向，故不可行
    if ((a[i] == 2 || a[i] == -2) && ((v / Len) - ((a[i] + v) / Len)))
      continue;
    map[v + a[i] / 2] = 1; // 在map地图对应位置赋值为1
    dig(v + a[i]);         //继续向下搜索
  }
}

void print()
{
  // 固定光标位置
  SetConsoleCursorPosition(GetStdHandle((DWORD)-11), (COORD){0});
  // 简单的遍历输出
  for (int i = 0; i < Len * Len; i++)
  {
    if (i - place)
    {
      map[i] ? color(7, BLACK) : color(0, BLUE);
      if (map[i] == 2)
        color(0, GREEN);
      if (map[i] == 3)
        color(0, YELLOW);
    }
    else
      color(0, RED);
    printf(" %d", map[i]);
    if (i % Len == Len - 1)
      _cputs("\n");
  }
}

_Bool inMap(int v)
{
  return v >= 0 && v < Len * Len;
}

// 曼哈顿距离
int manhattan(int v)
{
  int x = v % Len;
  int y = v / Len;
  int x1 = (Len * Len - Len - 1) % Len;
  int y1 = (Len * Len - Len - 1) / Len;
  return abs(x - x1) + abs(y - y1);
}
_Bool reachedEnd = 0;
void dfs(int v)
{
  if (v - (Len * Len - Len - 1) == 0) // 到达终点
    reachedEnd = 1;
  for (int x = 0; x < 4; x++)
  {
    print();
    Sleep(10);
    int t = v + move[x];
    if (inMap(t) && map[t] == 1)
    {
      map[t] = 2; // 路径标记为2
      dfs(t);
      if (!reachedEnd)
        map[t] = 3;
      else
        return;
    }
  }
  return;
}

int main()
{
  // 调整窗口大小，初始化随机种子
  srand((unsigned)malloc(!system("mode con:cols=62 lines=31")));
  // 隐藏光标
  SetConsoleCursorInfo(GetStdHandle((DWORD)-11), &(CONSOLE_CURSOR_INFO){25});

  dig(Len + 1);                            // 从起点(Len)开始打通墙，这样保证了最上下均不会被访问，即是墙，(len+1)表示在起点右边一个点开始，保证了最左右两边不会被访问
  map[Len] = map[Len * Len - Len - 1] = 1; // 起点(Len)和终点(Len * Len - Len - 1) 是 1(路)
  dfs(place + 1);
  for (c = 0; c = _getch(), place - (Len * Len - Len - 1);) //
  {                                                         // place到终点(Len * Len - Len - 1)停止
    if (c == 'q')                                           // 输入q退出
      break;
    for (i = 0; c - move[i + 4] && i < 4; i++)
      ; // 判断读入的是四个方向中的哪一个，i为索引
    if (i < 4 && map[place + move[i]])
    {                   // i 是adws中的一个且移动方向不是墙
      place += move[i]; // 根据move数组中的方向移动
    }
    print();
  }
  system("cls");
  if (c != 'q')
    printf("You Win!\n");
  system("pause");
}