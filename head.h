#pragma once
#include <graphics.h>  //ͼ�ν����ͷ�ļ�
#include <time.h>
#include <cstdlib>
#include <mmsystem.h>  //Ԥ����  ��ý���豸�ӿ�
#include <math.h>
#include<windows.h> 
#include <conio.h>
#pragma comment(lib,"winmm.lib")

#define NUM 13

//�̻����Ľṹ��
struct Jet
{
	int		x, y;	//��ǰ������
	int		hx, hy; //��ߵ������
	int		height; //y  hy ֮���  //Sleep()
	bool	shoot;  //�̻����Ƿ���
	DWORD	t1, t2, dt;  //�����ٶȵ�ʱ��
	IMAGE   img[2];      //2��Ԫ�ص�����  �±� 0 1 
	byte	n : 1;       //λ��
}jet[NUM];

//�̻��Ľṹ��
struct Fire
{
	int   r;			 //��ǰ�뾶
	int   maxr;			 //���뾶
	int   x, y;			 //����
	int   cen_x, cen_y;	 //���ĵ������
	int	  width, height; //ͼƬ�Ĵ�С
	int   xy[240][240];  //���ص�����  240*240  ͼ����  ��Ⱦ  

	bool  show;			//�Ƿ���ʾ
	bool  draw;			//�Ƿ����
	DWORD t1, t2, dt;   //��ը���ٶ�
}fire[NUM];

void Init(int i);
void Load();
void ChoiseRelu(DWORD& t1);
void Shoot();
void ShowFire(DWORD* pmem);
void Style(DWORD& st1);