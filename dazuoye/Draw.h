#pragma once
#include <Windows.h>
#include <stdio.h>
#include <io.h>
#include "Color.h"
#include "Utils.h"
using namespace std;
class Draw
{
	public:
		static void drawImage(const char* fileName);
		static void display();
};
/*
该函数可以在控制台画出一个bmp格式文件,参数为当前文件夹图片名

首先要搞清楚24位bmp图的结构
由三部分组成
1.文件头
文件头里面的信息是我们不需要的
2.信息头
这里面有图片的格式,宽度,高度等信息
3.位图数据
图片的像素详细信息;这里面的每个值都是0-255的数字,代表某个R,G或B的值
比如,开头三个连在一起是一个像素点的RGB值,然后接着三个又是下一个像素点,以此类推
*/
void Draw::drawImage(const char* fileName) 
{
	unsigned char* pBmpBuf;//读入图像数据的指针
	int bmpWidth;//图像的宽
	int bmpHeight;//图像的高
	int biBitCount;//图像类型&#xff0c;每像素位数
	BITMAPINFOHEADER head;//信息头
	FILE* fp = fopen(fileName, "rb");//fp为文件指针,fopen()为打开一个文件的函数,第一个参数为文件名,第二个为读取方式,r代表read读取,b代表byte字节
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);//fseek()表示在一个文件内寻找;参数依次为 文件指针  跳过的长度  开始位置
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);//freed表示 从文件fp里,读取1个长度为sizeof(BITMAPINFOHEADER)数据,储存到地址&head里
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	int lineByte = bmpWidth * biBitCount / 8;//每一行的字节数,因为像素RGB值分量有三个,所以这是应该是宽度*3,由于是24位图,所以/8;
	pBmpBuf = new unsigned  char[lineByte * bmpHeight];//定义指针指向的数据大小
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);//读取数据,将图片位图数据储存到已经开辟好的临时缓存区
	int i = bmpHeight * bmpWidth - bmpWidth;//i代表指针位置,由于位图数据的存储是倒过来的,所以第一行第一个应该是最后一行第一个
	int count = 1;//代表指针位于当前行的位置
	while (true)
	{
		//设置字体背景颜色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color::getColor(pBmpBuf[3 * i + 2], pBmpBuf[3 * i + 1], pBmpBuf[3 * i]).Value);
		//打印空格
		printf("  ");
		//当前行位置右移
		count++;
		//指针位置右移
		i++;
		//如果读到当前最后一行
		if (count == bmpWidth)
		{
			//指针进入上一行的第一个
			i = i - 2 * bmpWidth + 1;
			//位于当前行第一个
			count = 1;
			//图片打印换行
			printf("\n");
		}
		//如果读完,循环结束
		if (i < 0)
		{
			break;
		}
	}
	//将字体背景色设置回黑色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BLACK);
	fclose(fp);//关闭文件
}

void Draw::display()
{
	
	//std::filesystem::current_path(Utils::source());
	struct _finddata_t fileinfo;
	intptr_t hFile;
	while (true)
	{
		if ((hFile = _findfirst("*.bmp", &fileinfo)) == -1)
		{
			printf("there are no bmp files to read");
			return;
		}
		do
		{
			system("cls");
			Draw::drawImage(fileinfo.name);
			getchar();
		} while (_findnext(hFile, &fileinfo) == 0);
	}
	_findclose(hFile);
	return;
}
