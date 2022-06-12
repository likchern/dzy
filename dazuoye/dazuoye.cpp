#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#include "Draw.h"
/*
	先将图片信息都写入文本文件
	而后开始遍历文件夹
	在查找到一个图片后,先清屏,然后使用drawImage函数画出图片,使用getchar函数暂停程序
	由于最外面是个参数为true的while循环,所以遍历文件夹结束后会重新开始遍历,
	这样就会重新输出打印图片了
*/
int main() 
{
	Utils::iterate();
	stretch();
	Draw::display();
}



	
