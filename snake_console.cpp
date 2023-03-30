#include <windows.h>
#include <conio.h>
#include <iostream>

class snake
{
private:
  //custom
  int width, height, len, x, y;
  float speed;
  //reserved
  int *map;
  char direction = 'd', input = 'd';
  int i = 0, S = 0;

public:
  snake(int _width = 29, int _height = 29, float _speed = 10.0, int _len = 4, int _x = 0, int _y = 0) : width(_width), height(_height), speed(_speed), len(_len), x(_x), y(_y)
  {
    if (width > 58 || height > 29)
    {
      // 超出范围自动设为默认值
      if (width > 58)
        width = 29;
      if (height > 29)
        height = 29;
    }
    S = width * height;
    map = new int[S];
    for (int i = 0; i < S; i++)
      map[i] = 0;
    srand((unsigned)(long long)malloc(1));
  }
  int setup()
  {
    int t = (int)GetTickCount() / 1000;
    gotoxy();
    for (map[rand() % (S)] = -1; 1; Sleep(speed * 10)) //随机生成食物
    {
      if (_kbhit() && (input = _getch())) // 输入
      {
        if ((input == 'a' || input == 'A') && (direction != 'd'))
          direction = 'a';
        if ((input == 'd' || input == 'D') && (direction != 'a'))
          direction = 'd';
        if ((input == 's' || input == 'S') && (direction != 'w'))
          direction = 's';
        if ((input == 'w' || input == 'W') && (direction != 's'))
          direction = 'w';
      }
      switch (direction) //移动
      {
      case 'a':
        x -= (x > 0 ? 1 : -width + 1);
        break; //判断是否超出边界
      case 'd':
        x += (x < width - 1 ? 1 : -width + 1);
        break;
      case 'w':
        y -= (y > 0 ? 1 : -height + 1);
        break;
      case 's':
        y += (y < height - 1 ? 1 : -height + 1);
        break;
      }
      if (map[y * width + x] > 1)
        return (_cputs("\nGame Over!\n")); //判断是否吃到自己
      if (map[y * width + x] == -1)        //判断是否吃到食物
      {
        len++;
        do
          i = rand() % S;
        while (map[i]); //保证食物生成位置为空地
        map[i] = -1;    //生成食物
      }
      else
        for (i = 0; i < S; i++)
          if (map[i] > 0)
            map[i]--;           //蛇身移动
      map[y * width + x] = len; //蛇头赋值

      SetConsoleCursorPosition(GetStdHandle((DWORD)-11), COORD{0});
      for (i = 0; i < S; _cputs("  "), ++i % width || _cputs("\n"))
      {
        int t;
        if (map[i] > 0)
        {
          t = 208; //蛇身  0x00C0
        }
        else if (map[i])
          t = 192; //食物  0x00A0
        else
          t = 240; //空地  0x00F0
        SetConsoleTextAttribute(GetStdHandle((DWORD)-11), t);
      }
      printf("\nlen: %d time: %ds", len, (int)GetTickCount() / 1000 - t);
    }
  }
  void gotoxy() //隐藏光标
  {
    CONSOLE_CURSOR_INFO t{25};
    SetConsoleCursorInfo(GetStdHandle((DWORD)-11), &t);
  }
  ~snake()
  {
    delete[] map;
  }
};

int main()
{
  snake s(15, 7, 10, 2, 0, 0);
  s.setup();
  system("pause");
  return 0;
}