#include <iostream>
#include <graphics.h>	//easyx 图形库
#include <conio.h>

#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#define GRID_W 100		//格子的宽度
#define MAX_SIZE 4		//每行，列格子的数量
#define INTERVAL 15		//格子之间的间距

#define WIN_SIZE MAX_SIZE * GRID_W + (MAX_SIZE + 1)*INTERVAL	//窗口的宽度和高度

//枚举格子颜色
enum  Color
{
	zero = RGB(205, 193, 180),
	n_2 = RGB(238, 228, 218),
	n_4 = RGB(237, 224, 200),
	n_8 = RGB(242, 177, 121),
	n_16 = RGB(245, 149, 99),
	n_32 = RGB(246, 129, 95),
	n_64 = RGB(246, 94, 59),
	n_128 = RGB(242, 177, 121),
	n_256 = RGB(237, 204, 97),
	n_512 = RGB(255, 0, 128),
	n_1024 = RGB(145, 0, 72),
	n_2048 = RGB(242, 17, 158),
	back_c = RGB(187, 173, 160),
};
Color arr[] = {zero,n_2,n_4,n_8,n_16,n_32,n_64,n_128,n_256,n_512,n_1024,n_2048,back_c};

//定义数据数组
int map[MAX_SIZE][MAX_SIZE];

//生成2，4，2的概率比4大
int createNum()
{
	//seed参数，传入一个不断变化的量--time
	srand((unsigned)time(NULL) + clock());
	//rand()不会产生随机数，需要设置随机数种子srand()
	if (rand() % 6 == 0 || rand() % 6 == 2)
		return 4;
	else
		return 2;
}

void createNew_num()
{
	while (true)
	{
		int r = rand() % MAX_SIZE;
		int c = rand() % MAX_SIZE;
		if (map[r][c] == 0)
		{
			map[r][c] = createNum();
			break;
		}
	}
}

//初始化数据
void gameInit()
{
	for (int i = 0; i < 2;)
	{
		int r = rand() % MAX_SIZE;
		int c = rand() % MAX_SIZE;
		if (map[r][c] == 0) 
		{
			map[r][c] = createNum();
			i++;
		}
	}

}

//绘制界面
void gameDraw()
{
//	rectangle(20, 20, 80, 80);				//空心矩形
//	solidrectangle(120, 120, 180, 180);		//实心矩形

	//设置背景颜色
	setbkcolor(RGB(187, 173, 160));

	//清除绘图设备(屏幕)
	cleardevice();

	//绘制矩形
	for (int i = 0; i < MAX_SIZE; i++)
	{
		for (int k = 0; k < MAX_SIZE; k++)
		{
			//找到对应的格子左上角的坐标
			int x = k * GRID_W + (k + 1) * INTERVAL;
			int y = i * GRID_W + (i + 1) * INTERVAL;
			//设置填充颜色
			if (map[i][k] == 0)
				setfillcolor(arr[0]);
			else
			{
				int index = (int)log2((double)map[i][k]);
				COLORREF text_color = arr[index];
				setfillcolor(text_color);
				//setfillcolor(arr[index]);
			}
			//setfillcolor(RGB(205, 193, 180));
			//绘制格子
			//solidrectangle(x, y, x + GRID_W, y + GRID_W);
			//绘制圆角格子
			solidroundrect(x, y, x + GRID_W, y + GRID_W, 10, 10);

			if (map[i][k]!=0)
			{
				//设置文字的属性
				settextstyle(50, 0, "宋体");
				//设置文字背景透明
				setbkmode(TRANSPARENT);
				//设置字体颜色
				settextcolor(RGB(119, 110, 101));

				//整数转化成字符
				char str[10] = "";
				sprintf_s(str, "%d", map[i][k]);

				//求字符串的宽度和高度
				int temp_w = textwidth(str);
				int temp_h = textheight(str);
				//求字符串距离格子左边的距离
				int temp_x = (GRID_W - temp_w) / 2;
				int temp_y = (GRID_W - temp_h) / 2;
				outtextxy(x+temp_x, y+temp_y, str);
			}
			cout << map[i][k] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

//游戏操作,动态数组
void moveUp()
{
	bool or_create = false;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = 0;
		//第一次循环，合并相同数
		for (int j = 1; j < MAX_SIZE; j++)
		{
			if (map[j][i] != 0)
			{
				if (map[temp][i] == map[j][i])
				{
					map[temp][i] *= 2;
					map[j][i] = 0;
					temp = j;
				}
				else if (map[temp][i] == 0)
				{
					temp++;
				}
				else if (map[temp][i] != map[j][i])
				{
					temp = j;
				}
			}
		}
		//第二次循环，找0位，消除空位
		for (int j = 0; j < MAX_SIZE; j++)
		{
			if (map[j][i] == 0)
			{
				temp = j;
				break;
			}
		}
		for (int j = temp+1; j < MAX_SIZE; j++)
		{
			if (map[j][i] != 0)
			{
				map[temp][i] = map[j][i];
				map[j][i] = 0;
				temp++;
				or_create = true;
			}
		}
	}
	if (or_create)
	{
		createNew_num();
	}
	//for (int i = 0; i < max_size; i++)
	//{
	//	int temp = 0;
	//	for (int begin = 1; begin < max_size; begin++)
	//	{
	//		if (map[begin][i] != 0)
	//		{
	//			if (map[temp][i] == 0)
	//			{
	//				map[temp][i] = map[begin][i];
	//				map[begin][i] = 0;
	//			}
	//			else if (map[temp][i] == map[begin][i])
	//			{
	//				map[temp][i] *=2;
	//				map[begin][i] = 0;
	//				temp++;
	//			}
	//			else
	//			{
	//				map[temp + 1][i] = map[begin][i];
	//				if (temp + 1 != begin)
	//				{
	//					map[begin][i] = 0;
	//				}
	//				temp++;
	//			}
	//		}
	//	}
	//}
	//createnew_num();
}

void moveDown()
{
	bool or_create = false;
	for (int i = 0; i < MAX_SIZE; i++)
	{
		int temp = MAX_SIZE-1;
		//第一次循环，合并相同数
		for (int j = MAX_SIZE-2; j >=0; j--)
		{
			if (map[j][i] != 0)
			{
				if (map[temp][i] == map[j][i])
				{
					map[temp][i] *= 2;
					map[j][i] = 0;
					temp = j;
				}
				else if (map[temp][i] == 0)
				{
					temp--;
				}
				else if (map[temp][i] != map[j][i])
				{
					temp = j;
				}
			}
		}
		//第二次循环，找0位，消除空位
		for (int j = MAX_SIZE-1; j >=0; j--)
		{
			if (map[j][i] == 0)
			{
				temp = j;
				break;
			}
		}
		for (int j = temp-1; j >=0; j--)
		{
			if (map[j][i] != 0)
			{
				map[temp][i] = map[j][i];
				map[j][i] = 0;
				temp--;
				or_create = true;
			}
		}
	}
	if (or_create)
	{
		createNew_num();
	}
}

void moveLeft()
{

}

void moveRight()
{

}

//按键处理
void keyDeal()
{
	//获取键盘按键值
	char key = _getch();
	switch (key)
	{
	case 'w':
	case 'W':
	case 72:
	case 38:	//向上键盘值
		moveUp();
		break;
	case 's':
	case 'S':
	case 80:
	case 40:	//向下键盘值
		moveDown();
		break;
	case 'a':
	case 'A':
	case 75:
	case 37:	//向左键盘值
		moveLeft();
		break;
	case 'd':
	case 'D':
	case 77:
	case 39:	//向右键盘值
		moveRight();
		break;
	default:
		break;
	}
}

int main()
{
	//SHOWCONSOLE,显示控制台
	initgraph(WIN_SIZE, WIN_SIZE, SHOWCONSOLE);	//创建窗口
	gameInit();
	while (true)
	{
		gameDraw();
		keyDeal();
	}
	closegraph();	//关闭图形窗口
	return 0;
}