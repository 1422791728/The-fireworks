#include "head.h"

int main()
{
	//初始化一个窗口 宽 高
	initgraph(1200, 600);

	srand((unsigned int)time(0));

	//简单音乐播放
	mciSendString(L"open bk.mp3 alias music", 0, 0, 0);  //发送指令
	mciSendString(L"play music", 0, 0, 0);

	settextcolor(YELLOW);
	settextstyle(25, 0, L"楷体");
	outtextxy(400, 200, L"今天是弟弟的生日——05.12");
	outtextxy(400, 300, L"那我就先祝弟弟生日快乐");
	outtextxy(400, 350, L"希望弟弟以后的每一天都开开心心");
	outtextxy(400, 400, L"最后喜欢以后弟弟的生日里我不会缺席");
	outtextxy(400, 450, L"余生请多指教");
	outtextxy(400, 500, L"嘻嘻");
	outtextxy(700, 560, L"--古全仓");
	_getch();

	DWORD t1 = timeGetTime();
	DWORD* pmem = GetImageBuffer();
	DWORD st1 = timeGetTime();
	//初始化
	for (int i = 0; i < NUM; i++)
	{
		Init(i);
	}

	//加载图片
	Load();

	BeginBatchDraw();
	while (1)
	{
		for (int clr = 0; clr < 1000; clr++)
		{
			for (int j = 0; j < 2; j++)
			{
				int px1 = rand() % 1200;
				int py1 = rand() % 600;

				if (py1 < 790)  //像素越界
					pmem[py1 * 1200 + px1] = pmem[py1 * 1200 + px1 + 1] = BLACK;
			}
		}
		ChoiseRelu(t1);
		Shoot();
		ShowFire(pmem);
		Style(st1);
		FlushBatchDraw();
	}
	return 0;
}

//程序的初始化
void Init(int i)
{
	int r[NUM] = { 120, 120, 155, 123, 130, 147, 138, 138, 130, 135, 140, 132, 155 };
	int x[NUM] = { 120, 120, 110, 117, 110, 93, 102, 102, 110, 105, 100, 108, 110 };
	int y[NUM] = { 120, 120, 85, 118, 120, 103, 105, 110, 110, 120, 120, 104, 85 };

	fire[i].width = 240;
	fire[i].height = 240;
	fire[i].maxr = r[i];
	fire[i].cen_x = x[i];
	fire[i].cen_y = y[i];
	fire[i].show = false;
	fire[i].dt = 5;
	fire[i].t1 = timeGetTime();
	fire[i].r = 0;

	//初始化烟花弹
	jet[i].t1 = timeGetTime();  //获取系统的时间.
	jet[i].dt = rand() % 10;    //单位时间  dt=0-9 ms  y--.
	jet[i].n = 0;
	jet[i].shoot = false;		//是否发射.
} //img[2]  没有图片的.

  //加载图片
void Load()
{
	IMAGE flowerImg, fimg;
	loadimage(&flowerImg, L"flower.jpg", 3120, 240);
	for (int i = 0; i < NUM; i++)
	{
		SetWorkingImage(&flowerImg);
		getimage(&fimg, i * 240, 0, 240, 240);
		SetWorkingImage(&fimg);

		for (int m = 0; m < 240; m++)
		{
			for (int n = 0; n < 240; n++)
			{
				fire[i].xy[m][n] = getpixel(m, n);
			}
		}
	}

	//图片
	IMAGE shootImg;  //定义一个存放图片的对象  变量
	loadimage(&shootImg, L"shoot.jpg", 200, 50);  //图片的宽度和高度
												  //设置工作区
	for (int i = 0; i < NUM; i++)  //13个烟花弹
	{
		int n = rand() % 5;
		SetWorkingImage(&shootImg);
		getimage(&jet[i].img[0], n * 20, 0, 20, 50);
		getimage(&jet[i].img[1], (n + 5) * 20, 0, 20, 50);
	}
	SetWorkingImage(NULL); //工作区回到窗口
}

//选择  规则  
void ChoiseRelu(DWORD& t1)
{
	DWORD t2 = timeGetTime(); //获取系统时间

	if (t2 - t1 > 100)  //同时出现  13
	{
		int n = rand() % NUM;  //1-13
		if (jet[n].shoot == false && fire[n].show == false)
		{
			jet[n].x = rand() % 1180;
			jet[n].y = rand() % 100 + 600;  //0-750   800
			jet[n].hx = jet[n].x;
			jet[n].hy = rand() % 400;  //0-300
			jet[n].height = jet[n].y - jet[n].hy;
			jet[n].shoot = true;
			putimage(jet[n].x, jet[n].y, &jet[n].img[jet[n].n], SRCINVERT);
		}
		t1 = t2;
	}
}
//发射
void Shoot()
{
	for (int i = 0; i < NUM; i++)
	{
		//获取时间
		jet[i].t2 = timeGetTime();

		//满足t2-t1>dt  shoot 可以发射的
		if (jet[i].t2 - jet[i].t1 > jet[i].dt&& jet[i].shoot == true)
		{
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			//上升
			if (jet[i].y >= jet[i].hy)
			{
				jet[i].y -= 5;
				jet[i].n++;
			}

			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			//越是接近最高点3/4 开始减速
			if ((jet[i].y - jet[i].hy) * 4 < jet[i].height)  //height
			{
				jet[i].dt = rand() % 4 + 10;  //dt变大
			}

			//达到了最高点!!  烟花弹的坐标值 传递给 烟花
			if (jet[i].y <= jet[i].hy)
			{
				putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);
				fire[i].x = jet[i].x;
				fire[i].y = jet[i].hy;
				fire[i].show = true;
				jet[i].shoot = false;  //最高点  坐标值 传递给 烟花 爆炸
			}
			jet[i].t1 = jet[i].t2;
		}
	}
}

void ShowFire(DWORD* pmem)
{
	//dt 
	int  drt[16] = { 5, 5, 5, 5, 5, 6, 25, 25, 25, 25, 55, 55, 55, 55, 65, 65 };

	for (int i = 0; i < NUM; i++)
	{
		fire[i].t2 = timeGetTime();

		if (fire[i].t2 - fire[i].t1 > fire[i].dt&& fire[i].show == true)
		{
			if (fire[i].r < fire[i].maxr)
			{
				fire[i].r++;
				fire[i].dt = drt[fire[i].r / 10];
				fire[i].draw = true;
			}

			if (fire[i].r >= fire[i].maxr - 1)
			{
				fire[i].draw = false;
				Init(i);
			}
			fire[i].t1 = fire[i].t2;
		}

		//
		if (fire[i].draw)
		{
			for (double a = 0; a <= 6.28; a += 0.01)
			{
				int x1 = (int)(fire[i].cen_x + fire[i].r * cos(a));
				int y1 = (int)(fire[i].cen_y + fire[i].r * sin(a));

				if (x1 > 0 && x1 < fire[i].width && y1>0 && y1 < fire[i].height)
				{
					int b = fire[i].xy[x1][y1] & 0xff;   //blue
					int g = (fire[i].xy[x1][y1] >> 8) & 0xff;   //green
					int r = fire[i].xy[x1][y1] >> 16;   //red

					int xx = (int)(fire[i].x + fire[i].r * cos(a));
					int yy = (int)(fire[i].y - fire[i].r * sin(a));

					//
					if (r > 0x20 && g > 0x20 && b > 0x20 && xx < 1200 && xx>0 && yy > 0 && yy < 600)
					{
						pmem[yy * 1200 + xx] = BGR(fire[i].xy[x1][y1]);
					}

				}
			}
			fire[i].draw = false;
		}
	}
}

void Style(DWORD& st1)
{
	DWORD st2 = timeGetTime();

	if (st2 - st1 > 20000)  //20s
	{
		int  x[NUM] = { 60, 75, 91, 100, 95, 75, 60, 45, 25, 15, 25, 41, 60 };
		int  y[NUM] = { 65, 53, 40, 22, 5, 4, 20, 4, 5, 22, 40, 53, 65 };

		for (int i = 0; i < NUM; i++)
		{
			jet[i].x = x[i] * 10;
			jet[i].y = (y[i] + 75) * 10;
			jet[i].hx = jet[i].x;
			jet[i].hy = y[i] * 10;

			jet[i].height = jet[i].y - jet[i].hy;
			jet[i].shoot = true;
			jet[i].dt = 7;
			putimage(jet[i].x, jet[i].y, &jet[i].img[jet[i].n], SRCINVERT);

			fire[i].x = jet[i].x + 10;
			fire[i].y = jet[i].hy;
			fire[i].show = false;
			fire[i].r = 0;
		}
		st1 = st2;
	}
}

