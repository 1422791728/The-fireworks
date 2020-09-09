#pragma once
#include <graphics.h>  //图形界面的头文件
#include <time.h>
#include <cstdlib>
#include <mmsystem.h>  //预处理  多媒体设备接口
#include <math.h>
#include<windows.h> 
#include <conio.h>
#pragma comment(lib,"winmm.lib")

#define NUM 13

//烟花弹的结构体
struct Jet
{
	int		x, y;	//当前的坐标
	int		hx, hy; //最高点的坐标
	int		height; //y  hy 之间差  //Sleep()
	bool	shoot;  //烟花弹是否发射
	DWORD	t1, t2, dt;  //控制速度的时间
	IMAGE   img[2];      //2个元素的数组  下标 0 1 
	byte	n : 1;       //位段
}jet[NUM];

//烟花的结构体
struct Fire
{
	int   r;			 //当前半径
	int   maxr;			 //最大半径
	int   x, y;			 //坐标
	int   cen_x, cen_y;	 //中心点的坐标
	int	  width, height; //图片的大小
	int   xy[240][240];  //像素的数组  240*240  图像处理  渲染  

	bool  show;			//是否显示
	bool  draw;			//是否绘制
	DWORD t1, t2, dt;   //爆炸的速度
}fire[NUM];

void Init(int i);
void Load();
void ChoiseRelu(DWORD& t1);
void Shoot();
void ShowFire(DWORD* pmem);
void Style(DWORD& st1);