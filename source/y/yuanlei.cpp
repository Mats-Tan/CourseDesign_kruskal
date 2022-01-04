#ifndef A_H
#define A_H
#include<stdio.h>
#include<math.h>
#include <graphics.h>		// 引用 EasyX 绘图库头文件
#include <conio.h>
#define NUM 10000
#include <fstream>			//定义读写已命名文件的类型
#include <vector>
#include <sstream>			
#include <iostream>
#include<time.h>
#include <string>
using namespace std;
#undef UNICODE
#undef _UNICODE
#pragma warning(default: 4996)
#endif

//基础
//int Basic()
//{
//	initgraph(950, 680);			// 创建绘图窗口，分辨率 950x680
//	setbkcolor(WHITE);				// 设置背景色为白色
//	cleardevice();					// 用背景色清空屏幕
//	setcolor(RED);					// 设置绘图色为红色
//	circle(100, 240, 100);			// 画圆心为(100, 240)半径为100的圆
//	setlinecolor(BLUE);				// 改变颜色
//	rectangle(300, 300, 400, 400);	// 画矩形
//	setlinecolor(RGB(255, 255, 0));	// 用RGB改变颜色
//	line(500,100,400,200);			// 反斜线
//	line(200, 100, 300, 200);		// 斜线
//	line(600, 100, 600, 500);		// 竖线
//	line(200, 600, 600, 600);		// 横线
//	putpixel(900, 600, BLACK);		// 黑点
//	_getch();						// 按任意键退出
//	closegraph();					// 关闭图形界面
//	return 0;
//}



//输入坐标画多个圆
//int c()
//{
//	int x, y, m, n, cir[6][2], e = 0, f = 0;
//	printf("input the number of circles:\n");
//	scanf("%d", &x);
//	printf("%d\n", x);
//	for (m = 0; m < x; m++)
//	{
//		for (n = 0; n < 2; n++)
//		{
//			scanf("%d", &cir[m][n]);
//		}
//	}
//	initgraph(950, 680);
//	setbkcolor(WHITE);				// 设置背景色为白色
//	cleardevice();					// 用背景色清空屏幕
//	setcolor(RED);					// 设置绘图色为红色initgraph(950, 680);
//	setbkcolor(WHITE);				// 设置背景色为白色
//	cleardevice();					// 用背景色清空屏幕
//	setcolor(RED);					// 设置绘图色为红色
//	for (m = 0; m < x; m++)
//	{
//		e = cir[m][0];
//		f = cir[m][1];
//		circle(e, f, 30);
//	}
//	_getch();
//	closegraph();					// 关闭图形界面
//	return 0;
//}


//输出多个圆，用线相连
//int lian()
//{
//	int x, y, m, n, cir[NUM][2], e = 0, f = 0, g, h;
//	printf("input the number of circles:\n");
//	scanf("%d", &x);
//	printf("%d\n", x);
//	for (m = 0; m < x; m++)
//	{
//		for (n = 0; n < 2; n++)
//		{
//			scanf("%d", &cir[m][n]);
//		}
//	}
//	initgraph(950, 680);
//	setbkcolor(WHITE);				// 设置背景色为白色
//	cleardevice();					// 用背景色清空屏幕
//	setcolor(RED);					// 设置绘图色为红色initgraph(950, 680);
//	setbkcolor(WHITE);				// 设置背景色为白色
//	cleardevice();					// 用背景色清空屏幕
//	setcolor(RED);					// 设置绘图色为红色
//	for (m = 0; m < x; m++)
//	{
//		e = cir[m][0];
//		f = cir[m][1];
//		circle(e, f, 30);
//		n = m + 1;
//		if (n < x)
//		{
//			e = cir[m][0];
//			f = cir[m][1];
//			g = cir[n][0];
//			h = cir[n][1];
//			line(e, f, g, h);
//		}
//	}
//	_getch();
//	closegraph();					// 关闭图形界面
//	return 0;
//}



//在线中间输出文字
//int word()
//{
//	int a, x, y, c, d, e, f;
//	scanf("%d", &a);
//	scanf("%d", &x);
//	scanf("%d", &y);
//	scanf("%d", &c);
//	scanf("%d", &d);
//	printf("%d\t%d\t%d\n", a, x, y);
//	if (a == 1)
//	{
//		initgraph(950, 680);			// 创建绘图窗口，分辨率 950x680
//		setbkcolor(WHITE);				// 设置背景色为白色
//		cleardevice();					// 用背景色清空屏幕
//		setcolor(RED);					// 设置绘图色为红色
//		line(x, y, c, d);
//		e = fabs(x - c);
//		f = fabs(y - d);
//		outtextxy(e + 20, f - 20, "beijing   shanghai");
//	}
//	else
//	{
//		if (a == 0)
//			printf("something is error!");
//		else
//			printf("something is error!");
//	}
//	_getch();						// 按任意键退出
//	closegraph();					// 关闭图形界面
//	return 0;
//}



//文字与斜线平行,使之与直线的大小而变化
//#include<stdio.h>
//#include<math.h>
//#include <graphics.h>		
//#include <conio.h>
//#include <string>
//#pragma warning(default: 4996)
//
//#define PI 3.14159265
//
//int caculate(int xy[4]) //计算字体大小，使之与直线的大小而变化
//{
//	return (int)(sqrt((double)((xy[0] - xy[2]) * (xy[0] - xy[2]) + (xy[1] - xy[3]) * (xy[1] - xy[3])))/20);
//}
//
//double Kvalue(int xy[4]) //计算斜线的K值
//{
//	double d = (double)(xy[3] - xy[1]) / (double)(xy[2] - xy[0]);
//	d = atan(d)*180/PI;
//	return d;
//}
//
//int value(int xy[4]) //计算K的正负
//{
//	double d = Kvalue(xy);
//	int k = (double)(xy[3] - xy[1]) / (double)(xy[2] - xy[0]);
//	if (k != 0) {
//		k = k / abs(k);
//	}
//	k = k * (int)d;
//	return k;
//}
//
//int Drawline(int xy[4])//设置画图相关与字体
//{
//	int fondSize = caculate(xy);
//	int tx, ty;
//	tx = abs(xy[2] + xy[0])/2; ty = abs(xy[3] + xy[1])/2;
//	int k = value(xy)*10;
//		initgraph(950, 680);			//创建绘图窗口，分辨率 950x680
//		setbkcolor(WHITE);				// 设置背景色为白色
//		cleardevice();					// 用背景色清空屏幕
//		setcolor(RED);					// 设置绘图色为红色
//		settextstyle(fondSize, 0, _T("微软雅黑"), k, k, FW_BOLD, false, false,false);
//		outtextxy(tx, ty, "11780");
//		line(xy[0], xy[1], xy[2], xy[3]);
//	_getch();						// 按任意键退出
//	closegraph();					// 关闭图形界面
//	return 0;
//}
//
//int main() {
//	int	xy[4] = { 500,100,300,300 };
//	Drawline(xy);
//
//}



//读取csv文件
//int vv()
//{
//	char buff[1000];
//	FILE* fp = fopen("C:/Users/YL/Desktop/res.csv", "r");
//	if (NULL == fp)
//	{
//		printf("read file fail\n");
//	}
//
//	while (fgets(buff, sizeof(buff), fp) != NULL)
//	{
//		printf("%s", buff);
//	}
//	return 0;
//}



//时间戳写入文件
//int timetxt()
//{
//	time_t timeSec = time(NULL); //获取1970.1.1至当前秒数time_t
//	struct tm* timeinfo = localtime(&timeSec); //创建TimeDate,并转化为当地时间，
////	struct tm * timeinfo = gmtime ( &timeSec ); //创建TimeDate,并转化为GM时间，
//	printf("The current date/time is: %s\n", asctime(timeinfo));//获取年 月 日 时 分 秒 对应的int值：
//	printf("%d-%d-%d %d:%d:%d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
//	FILE* fp = fopen("yuan.txt", "w");
//	fprintf(fp, "timetxt() has run! %d-%d-%d %d:%d:%d\n", timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
//	return 0;
//}

