#pragma once
#include <Windows.h>
#include <cmath>
/*
求近似颜色
按照老师给的图片,这些都是24位的bmp图片,所以从其位图数据可以得到每个像素的RGB值分量,R为red,G为green,B为blue
通过RGB可以显示的颜色是很多种的,而控制台只有16种背景颜色,下面列出了14种
所以我们要将每个像素的颜色近似成这14种颜色
你可以将R,G,B想象成X,Y,Z,建立一个空间坐标系,所以,哪两个点的距离最近那么颜色也就最接近
*/
WORD RED = BACKGROUND_RED | BACKGROUND_INTENSITY;//red: 255 green: 0  blue: 0
WORD RED_DARK = BACKGROUND_RED;//128,0,0
WORD BLUE = BACKGROUND_BLUE | BACKGROUND_INTENSITY;//0 0 255
WORD BLUE_DARK = BACKGROUND_BLUE;//0,0,128
WORD GREEN = BACKGROUND_GREEN | BACKGROUND_INTENSITY;//0 255 0
WORD GREEN_DARK = BACKGROUND_GREEN;//0,128,0
WORD MAGENTA = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;//255 0 255
WORD MAGENTA_DARK = BACKGROUND_BLUE | BACKGROUND_RED;//128,0,128
WORD CYAN = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;//0 255 255
WORD CYAN_DARK = BACKGROUND_GREEN | BACKGROUND_BLUE;//0,128,128
WORD YELLOW = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;//255 255 0
WORD YELLOW_DARK = BACKGROUND_RED | BACKGROUND_GREEN;//128,128,0
WORD BLACK = 0;//0,0 0
WORD WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;//255 255 255
WORD BLACK_BRIGHT = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; //128 128 128
WORD WHITE_DARK = BACKGROUND_INTENSITY; //192 192 192
/*
建立一个Color类,里面有四个属性
int R;  RGB中的红色分量
int G;	RGB中的绿色分量
int B;	RGB中的蓝色分量
WORD value;	SetConsoleTextAttribute()中第二个参数的类型,也就是字体背景颜色
还有一个以这四个为参数的构造函数
*/
class Color {
public:
	WORD Value;
	int R, G, B;
	Color(WORD value, int r, int g, int b)
	{
		Value = value;
		R = r;
		G = g;
		B = b;
	};
	static Color getColor(int r, int g, int b);
	/*
建立一个Color类数组,将上面十四种颜色变成Color类都储存进去
*/
};

Color colors[14] = { 
	Color(RED,231,72,86),
	Color(RED_DARK,197,15,31),
	Color(BLUE,59,120,255),
	Color(BLUE_DARK,0,55,218),
	Color(GREEN,22,198,12),
	Color(GREEN_DARK,19,161,14),
	Color(MAGENTA,180,0,158),
	Color(MAGENTA_DARK,136,23,152),
	Color(CYAN,97,214,214),
	Color(CYAN_DARK,58,150,221),
	Color(YELLOW,249,241,165),
	Color(YELLOW_DARK,193,156,0),
	Color(BLACK,12,12,12),
	Color(WHITE,242,242,242),
	/*Color(BLACK_BRIGHT,	118,118,118),
	Color(WHITE_DARK,204,204,204)*/
};
/*
这个方法就是得到一个颜色的近似色
参数为一个像素的RGB值的三个分量
原理:
value代表这个像素点与数组里某个颜色的"距离"(RGB类比XYZ),将value一开始设置的尽量大点
tmp是临时储存一个"距离"
index代表colors数组的第几个颜色
pow(x,y)代表x的y次方
进行一个for循环,将传入的颜色与每个颜色对比
最后返回距离最近的颜色
*/
Color Color::getColor(int r, int g, int b) 
{
	int value = 1000000;
	int tmp = 0;
	int index = 10;
	for (int i = 0; i < 14; i++)
	{
		tmp = int(pow((colors[i].R - r), 2) + pow((colors[i].G - g), 2) + pow((colors[i].B - b), 2));
		if (tmp <= value)
		{
			value = tmp;
			index = i;
		}
	}
	return colors[index];
}