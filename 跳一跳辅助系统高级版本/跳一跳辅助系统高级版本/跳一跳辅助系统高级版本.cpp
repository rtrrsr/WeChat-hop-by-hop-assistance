/**
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <graphics.h>
#include "atlimage.h"


IMAGE image;	//��������ͼƬ
IMAGE img;		//�������ͼƬ
int xy[800][700];		//����img�������е����ص�
int x, y;		//����
DWORD* pMem;		//�����Դ�
int  x1, y2;
int x3, y3;
char str[100];

BOOL ColorFun(COLORREF color1, COLORREF color2, int deff);
BOOL isNewBlock(int color);

int main()
{
	while (1)
	{
		//initgraph(800, 700);		//��ʼ������
		//pMem = GetImageBuffer(NULL);		//��ȡ�õ����ڵ��Դ�

		system("adb shell screencap -p /sdcard/screen.png");		//��ȡ�ֻ�����
		system("adb pull /sdcard/screen.png");		//�����ֻ�����

		CImage cimage;
		cimage.Load(L"screen.png");
		cimage.Save(L"screen.jpg");

		loadimage(&image, TEXT("screen.jpg"));		//��screen.png���浽image

													//�и�ͼƬ
		SetWorkingImage(&image);		//���õ�ǰ�Ĺ�����Ϊimage
		getimage(&img, 100, 600, 800, 700);
		SetWorkingImage(&img);

		for (y = 0; y < 700; y++)
		{
			for (x = 0; x < 800; x++)
			{
				xy[x][y] = getpixel(x, y);		//getpixel��ȡ���ص� ����
				if (isNewBlock(xy[x][y]))
				{
					x1 = x;
					y2 = y;
					goto next;
				}
			}
		}
	next:
		//�˵�λ��
		for (y = 699; y > 0; y--)
		{
			for (x = 0; x < 800; x++)
			{
				xy[x][y] = getpixel(x, y);
				if (ColorFun(xy[x][y], RGB(55, 60, 100), 10))
				{
					x3 = x;
					y3 = y;
					break;
				}
			}
			if (ColorFun(xy[x][y], RGB(55, 60, 100), 10))
			{
				x3 = x;
				y3 = y;
				break;
			}
		}

		//Ҫ����Ŀ���
		int xxx = x1 + 7;
		int yyy = y2 + 95;

		int dis = sqrt(double((yyy - y3)*(yyy - y3) + (xxx - x3)*(xxx - x3)));
		int time = 1.35*dis;

		//SetWorkingImage(NULL);		//���õ�ǰ�Ĺ�����Ϊ����
		//putimage(0, 0, &img);		//��image���������ڴ������� 0,0,
		//getchar();
		//cleardevice();		//�����Ļ
		//for (x = 0; x < 800; x++)
		//{
		//	for (y = 0; y < 700; y++)
		//	{
		//		int b = xy[x][y] & 0xff;		//�Ͱ�λ
		//		int g = (xy[x][y] >> 8) & 0xfff;		//�Ͱ�λȥ�� ��ȡ�Ͱ�λ
		//		int r = xy[x][y] >> 16;		//��ʮ��λ
		//		pMem[y * 800 + x] = BGR(xy[x][y]);
		//	}
		//}
		//FlushBatchDraw();		//�ѻ��Ƶ�ͼƬ��ʾ����
		char str[100];
		sprintf(str, "adb shell input swipe 200 200 205 305 %d", time);
		system(str);

		Sleep(50);
	}
	//closegraph();		//	�ر�ͼ�ν���
	//system("pause");
	return 0;
}

BOOL ColorFun(COLORREF color1, COLORREF color2, int deff)		//�ж���ɫ�Ƿ�����
{
	int r1 = GetRValue(color1);
	int g1 = GetGValue(color1);
	int b1 = GetBValue(color1);

	int r2 = GetRValue(color2);
	int g2 = GetGValue(color2);
	int b2 = GetBValue(color2);

	if (sqrt(double((r2 - r1)*(r2 - r1) + (g2 - g1)*(g2 - g1) + (b2 - b1)*(b2 - b1))) < deff)
		return TRUE;

	return FALSE;
}

//���ϵĻ�ȡ��������
BOOL isNewBlock(int color)
{
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);
	//����ɫ
	if (ColorFun(color, RGB(243, 245, 242), 5))
	{
		return TRUE;
	}
	if (ColorFun(color, RGB(252, 254, 251), 5))
	{
		return TRUE;
	}
	if (ColorFun(color, RGB(239, 241, 238), 3))
	{
		return TRUE;
	}
	//ǳ��ɫ
	else if (ColorFun(color, RGB(245, 245, 240), 5))
	{
		return TRUE;
	}
	//ī��ɫ
	else if (ColorFun(color, RGB(98, 149, 102), 10))
	{
		return TRUE;
	}
	//���ɫ
	else if (ColorFun(color, RGB(110, 102, 109), 10))
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(110, 112, 109), 10))
	{
		return TRUE;
	}
	//��ɫ
	else if (ColorFun(color, RGB(245, 128, 58), 10))
	{
		return TRUE;
	}
	//ǳ��ɫ
	else if (ColorFun(color, RGB(186, 239, 63), 10))
	{
		return TRUE;
	}
	//ľ������
	else if (ColorFun(color, RGB(229, 196, 159), 5))
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(234, 203, 174), 5))
	{
		return TRUE;
	}
	//��ɫ
	else if (ColorFun(color, RGB(254, 240, 89), 5))
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(254, 238, 95), 5))
	{
		return TRUE;
	}
	//��ɫ���
	else if (r > 124 && r < 134 && g>111 && g < 121 && b>219 && b < 229)
	{
		return TRUE;
	}
	//��Բ������
	else if (r > 75 && r < 85 && g>158 && g < 168 && b>85 && b < 95)
	{
		return TRUE;
	}
	//��ɫ
	else if (ColorFun(color, RGB(254, 74, 83), 10))
	{
		return TRUE;
	}
	//����ʯ
	else if (ColorFun(color, RGB(152, 114, 111), 10))
	{
		return TRUE;
	}
	//��Ͱ
	else if (ColorFun(color, RGB(117, 117, 117), 10))
	{
		return TRUE;
	}
	else if (ColorFun(color, RGB(225, 199, 142), 10))
	{
		return TRUE;
	}
	//�鱾
	else if (ColorFun(color, RGB(241, 241, 241), 10))
	{
		return TRUE;
	}
	//��ɫ����
	else if (ColorFun(color, RGB(255, 172, 178), 10))
	{
		return TRUE;
	}
	//�̲豭��
	else if (ColorFun(color, RGB(73, 73, 73), 10))
	{
		return TRUE;
	}
	//���Ƴ�Ƭ��
	else if (ColorFun(color, RGB(147, 147, 147), 10))
	{
		return TRUE;
	}
	return FALSE;
}
*/

#include <stdio.h>
#include <windows.h>
#include <graphics.h>
#include "atlimage.h"
#include <time.h>

IMAGE image, img; // ��ͼͼ��
int coor[800][700]; // �����ͼ������������е����ص�
int blockX, blockY; // Ŀ�귽�鶥������
int peopleX, peopleY; // ��ɫ������
int touchX, touchY; // ģ�ⰴ�µ�����
int x, y;
char str[100];

BOOL isNewBlock(int color);
BOOL colorFun(COLORREF color1, COLORREF color2, int diff);

int main()
{
	srand((unsigned int)time(NULL));
	while (1)
	{
		// ��ͼ������
		printf("capturing data and screen��");
		system("adb shell screencap -p /sdcard/screen.png");
		system("adb pull /sdcard/screen.png");
		// ��ͼ��ʽת�� png -> jpg
		CImage cimage;
		cimage.Load(L"screen.png");
		cimage.Save(L"screen.jpg");
		loadimage(&image, L"screen.jpg"); // �ѽ�ͼ���浽image
										  // �и�ͼƬ��ȡ����Ϸ������������Ϸ���򣬼ӿ��ж�Ч��
		SetWorkingImage(&image);
		getimage(&img, 100, 600, 800, 700);
		SetWorkingImage(&img);
		printf("getting the role and block location...\n");
		// ɨ���ɫ���꣬�������ϣ���������ɨ�赽ͷ����ֹͣ��
		for (y = 699; y >= 0; y--)
		{
			for (x = 0; x < 800; x++)
			{
				coor[x][y] = getpixel(x, y);// �������ص�
				if (colorFun(coor[x][y], RGB(55, 60, 100), 10))
				{
					peopleX = x;
					peopleY = y;
					goto getRole;
				}
			}
		}
	getRole:
		//  �жϽ�ɫ����߻����ұߣ��ӿ�ͼ���ж�Ч�ʣ�����С�η����bug
		for (y = 0; y < 700; y++)
		{
			for (x = ((peopleX < 400) ? peopleX + 60 : 0); x < ((peopleX < 400) ? 800 : peopleX - 60); x++)
			{
				coor[x][y] = getpixel(x, y); // ��ȡ���ص�
				if (isNewBlock(coor[x][y])) // �ж��Ƿ����µĺ���
				{
					blockX = x;
					blockY = y;
					goto getBlock;
				}
			}
		}
	getBlock:
		printf("calculate jump and touch coordinates...\n");
		// ����Ŀ���
		int targetX = blockX + 10;
		int targetY = blockY + 95;
		// �������������ģ����ָ�������꣬����Ҽ��
		touchX = rand() % 80 + 200; // 200-279
		touchY = rand() % 85 + 300; // 300-384
		int distance = sqrt(double((targetY - peopleY)*(targetY - peopleY) + (targetX - peopleX)*(targetX - peopleX)));
		int time = 1.35 * distance;
		sprintf(str, "adb shell input swipe %d %d %d %d %d", touchX, touchY, touchX + 1, touchY + 1, time);
		printf("executing��(%d,%d)->(%d,%d) touching (%d,%d) for %dms\n", peopleX, peopleY, targetX, targetY, touchX, touchY, time);
		system(str);
		Sleep(1500);
	}
	return 0;
}

// �ж���ɫ�Ƿ����ƣ�diff ԽСԽ����
BOOL colorFun(COLORREF color1, COLORREF color2, int diff)
{
	return sqrt(double((GetRValue(color2) - GetRValue(color1))*(GetRValue(color2) - GetRValue(color1)) + (GetGValue(color2) - GetGValue(color1))*(GetGValue(color2) - GetGValue(color1)) + (GetBValue(color2) - GetBValue(color1))*(GetBValue(color2) - GetBValue(color1)))) < diff;
}

// �ж��Ƿ����µĺ���
BOOL isNewBlock(int color)
{
	int r = GetRValue(color);
	int g = GetGValue(color);
	int b = GetBValue(color);

	if (colorFun(color, RGB(246, 246, 246), 10))//ǳ��ɫ
		return TRUE;
	else if (colorFun(color, RGB(250, 250, 250), 10))
		return TRUE;
	else if (colorFun(color, RGB(255, 255, 255), 0))//����ɫ
		return TRUE;
	else if (colorFun(color, RGB(100, 148, 106), 20))//ī��ɫ
		return TRUE;
	else if (colorFun(color, RGB(113, 113, 113), 10))//���ɫ 
		return TRUE;
	else if (colorFun(color, RGB(245, 128, 58), 10))//��ɫ
		return TRUE;
	else if (colorFun(color, RGB(186, 239, 69), 10))//ǳ��ɫ
		return TRUE;
	else if (colorFun(color, RGB(234, 203, 174), 10))//ľ������
		return TRUE;
	else if (colorFun(color, RGB(254, 240, 89), 10))//��ɫ
		return TRUE;
	else if (r > 124 && r < 134 && g>111 && g < 121 && b > 219 && b < 229)//��ɫ���
		return TRUE;
	else if (r > 75 && r < 85 && g>158 && g < 165 && b > 85 && b < 95)//��Բ������
		return TRUE;
	else if (colorFun(color, RGB(254, 74, 83), 10))//��ɫ
		return TRUE;
	else if (colorFun(color, RGB(152, 114, 111), 10))//����ʯ
		return TRUE;
	else if (colorFun(color, RGB(117, 117, 117), 10))//��Ͱ
		return TRUE;
	else if (colorFun(color, RGB(225, 199, 142), 10))
		return TRUE;
	else if (colorFun(color, RGB(241, 241, 241), 10))//�鱾
		return TRUE;
	else if (colorFun(color, RGB(255, 172, 178), 10))//��ɫ����
		return TRUE;
	else if (colorFun(color, RGB(73, 73, 73), 3))//�̲豭��
		return TRUE;
	else if (colorFun(color, RGB(147, 147, 147), 10))//���Ƴ�Ƭ��
		return TRUE;
	return FALSE;
}
