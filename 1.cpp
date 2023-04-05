#include <windows.h>
#include <conio.h>
#include <stdio.h>

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

#define LEN 15
int map[LEN * LEN] = {0};

void init()
{
  int i, j;
  for (i = 0; i < LEN; i++)
  {
    for (j = 0; j < LEN; j++)
    {
      if (i == 0 || j == 0 || i == LEN - 1 || j == LEN - 1)
      {
        map[i * LEN + j] = 1;
      }
    }
  }
  map[1 * LEN + 1] = 2;                 // 起点(1,1)
  map[(LEN - 2) * LEN + (LEN - 2)] = 3; // 终点(LEN-2,LEN-2)
  // 障碍物
  map[5 * LEN + 5] = 1;
  map[5 * LEN + 6] = 1;
  map[5 * LEN + 7] = 1;
  map[4 * LEN + 6] = 1;
}

/**
 * @brief 曼哈顿距离
 * 
 * @param x1 
 * @param y1 
 * @param x2 
 * @param y2 
 * @return int 
 */
int manhattan_distance(int x1,int y1,int x2,int y2) {
  return abs(x1-x2)+abs(y1-y2);
}

int aStar(int x,int y,int curr_cost) {
  int x0,y0;
  int min_cost=9999;
  int dir[4][2]={{0,1},{1,0},{0,-1},{-1,0}}; // 四个方向 0右 1下 2左 3上
  for (int i=0;i<4;i++) {
    if (map[(x+dir[i][0])*LEN+(y+dir[i][1])]==3) {
      return curr_cost+1;
    }
    if (map[(x+dir[i][0])])
  }
}

int main()
{
  init();
  int i, j;
  CONSOLE_CURSOR_INFO cursor_info = {25};
  SetConsoleCursorInfo(GetStdHandle((DWORD)-11), &cursor_info);
  // vscode控制台清空
  color(0, 0);
  printf("\033[2J");
  for (;;)
  {
    COORD pos = {0, 0};
    SetConsoleCursorPosition(GetStdHandle((DWORD)-11), pos);
    for (i = 0; i < LEN; i++)
    {
      for (j = 0; j < LEN; j++)
      {
        if (map[i * LEN + j] == 1)
          color(0, 48);
        else if (map[i * LEN + j] == 2)
          color(0, 32);
        else if (map[i * LEN + j] == 3)
          color(0, 64);
        else if (map[i * LEN + j] == 4)
          color(0, 96);
        else
          color(0, 128);
        _cputs("  ");
      }
      printf("\n");
    }
    Sleep(30);
  }
  system("pause");
}