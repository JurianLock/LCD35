/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*树莓派通过74HC164串行转并行芯片输出数据至TFT[0：7]引脚；IM0 = IM1 = 1;(8位并行)
*
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <wiringPi.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysinfo.h>
#include "r61581.h"

//#include "shuzu.H"

int table[] =
{
0xFFFF,0x0000,0xF7DE,0xDF3C,
0xEF9E,0x738E,0x00CC,0x0013,
0x051F,0x019F,0x7FFF,0xF800,
0xF81F,0x07E0,0x7FFF,0xFFE0,
0x18A3
};

void init_gpio( )
{
//GPIO初始化;
//设置树莓派GPIO为输出模式
pinMode (DAT, OUTPUT) ;
pinMode (DAT1, OUTPUT) ;
pinMode (CLK, OUTPUT) ;
pinMode (RD, OUTPUT) ;
pinMode (WR, OUTPUT) ;
pinMode (CS, OUTPUT) ;
pinMode (RS, OUTPUT) ;
pinMode (RST, OUTPUT) ;
pinMode (BUSY, OUTPUT) ;
}

/****************写指令**************
*由数据手册时序（16位并口）
****************写指令**************/
void TFT_wcmd(u16 cmd)
{
RST_1;//取消复位
RD_1;//——读引脚
CS_1;//——片选
CS_0;//——片选有效
RS_0;//——低为写指令
WR_0;//——写引脚
delayMicroseconds(1);
sendbyte(cmd);//——写入数据
delayMicroseconds(1);
WR_1;//——写引脚
CS_1;//——释放TFT
}

/***************写数据********************
*由数据手册时序（16位并口）
***************写数据********************/
void TFT_wdat(u16 dat)
{
RST_1;//取消复位
RD_1;//——读引脚
CS_1;//——片选


CS_0;//——片选有效
RS_1;//——高为写数据
WR_0;//——写引脚
delayMicroseconds(1);//微妙延时 必须加 不然 TFT 会有局域像素花屏
sendbyte(dat);//——写入数据
delayMicroseconds(1);
WR_1;//——写引脚
CS_1;//——释放TFT
}


/*******************TFT初始化************************/
void TFT_init()
{
init_gpio();
CS_1;RS_1;WR_1;RD_1;
RST_1;
// delayMicroseconds(100);
RST_0;
//delayMicroseconds(100);
RST_1;CS_0;

TFT_wcmd(0xFF);
TFT_wcmd(0xFF);
//delay(5);
TFT_wcmd(0xFF);
TFT_wcmd(0xFF);
TFT_wcmd(0xFF);
TFT_wcmd(0xFF);
//delay(1);


TFT_wcmd(0x11);
//delay(15);


TFT_wcmd(0xB0);
TFT_wdat(0x00);


TFT_wcmd(0xB3);
TFT_wdat(0x02);
TFT_wdat(0x00);
TFT_wdat(0x00);
TFT_wdat(0x00);


TFT_wcmd(0xB9);
TFT_wdat(0x01);
TFT_wdat(0x0);
TFT_wdat(0x0F);
TFT_wdat(0x0F);


TFT_wcmd(0xC0);
TFT_wdat(0x13);
TFT_wdat(0x3B);
TFT_wdat(0x00);
TFT_wdat(0x00);
TFT_wdat(0x00);
TFT_wdat(0x01);
TFT_wdat(0x00);
TFT_wdat(0x43);


TFT_wcmd(0xC1);
TFT_wdat(0x08);
TFT_wdat(0x1B);
TFT_wdat(0x08);
TFT_wdat(0x08);


TFT_wcmd(0xC4);
TFT_wdat(0x11);
TFT_wdat(0x01);
TFT_wdat(0x73);
TFT_wdat(0x01);


TFT_wcmd(0xC6);
TFT_wdat(0x00);


TFT_wcmd(0xC8);
TFT_wdat(0x0F);
TFT_wdat(0x05);
TFT_wdat(0x14);
TFT_wdat(0x5C);
TFT_wdat(0x03);
TFT_wdat(0x07);
TFT_wdat(0x07);
TFT_wdat(0x10);
TFT_wdat(0x00);
TFT_wdat(0x23);


TFT_wdat(0x10);
TFT_wdat(0x07);
TFT_wdat(0x07);
TFT_wdat(0x53);
TFT_wdat(0x0C);
TFT_wdat(0x14);
TFT_wdat(0x05);
TFT_wdat(0x0F);
TFT_wdat(0x23);
TFT_wdat(0x00);


TFT_wcmd(0x35);
TFT_wdat(0x00);


TFT_wcmd(0x36);//屏幕文字方向
//TFT_wdat(0x60);
//TFT_wdat(0x00);
TFT_wdat(0x41);
//TFT_wdat(0x10);


TFT_wcmd(0x3A);
TFT_wdat(0x55);


TFT_wcmd(0x44);
TFT_wdat(0x00);
TFT_wdat(0x01);


TFT_wcmd(0xD0);
TFT_wdat(0x07);
TFT_wdat(0x07);
TFT_wdat(0x1D);
TFT_wdat(0x03);


TFT_wcmd(0xD1);
TFT_wdat(0x03);
TFT_wdat(0x5B);
TFT_wdat(0x10);


TFT_wcmd(0xD2);
TFT_wdat(0x03);
TFT_wdat(0x24);
TFT_wdat(0x04);


TFT_wcmd(0x21);
TFT_wcmd(0x29);


//delay(3);


TFT_wcmd(0x2A);
TFT_wdat(0x00);
TFT_wdat(0x00);
TFT_wdat(0x01);
TFT_wdat(0xDF);//480


TFT_wcmd(0x2B);
TFT_wdat(0x00);
TFT_wdat(0x00);
TFT_wdat(0x01);
TFT_wdat(0x3F);//320


TFT_R61581_Clear(0x0001);


TFT_wcmd(0x2C);
delay(500);
}


/*****************************************************************
*功能：TFT背光控制
*参数： duty 占空比
*调用： TFT_back(240)；
****************************************************************/
void TFT_back(u8 duty)
{
TFT_wcmd(0xB9);
TFT_wdat(0x01);
TFT_wdat(duty);
TFT_wdat(0x3F);
TFT_wdat(0x0F);
TFT_wcmd(0x2C);
}


/****************************************************************************
* 功能：将屏幕填充成指定的颜色 清屏
*参数：Color填充值
* 调用：TFT_R61581_Clear(0xffff);
****************************************************************************/
void TFT_R61581_Clear(u16 Color)
{
u32 temp;
TFT_Set_Window(0,0,319,479);
CS_0//选择TFT
RD_1
RS_1//操作RAM
sendbyte(Color);
for(temp=0;temp<153600;temp++)
{
WR_0
WR_1
}
CS_1//释放TFT
}


/************************************************************************
*功能：设置窗口
*参数： X Y窗口坐标
*说明：窗口大小:(ex-sx+1)*(ey-ex+1) 注意,确保ex>=sx;ey>=sy
*调用： TFT_Set_Window(0,0,479,319);
***********************************************************************/
void TFT_WriteRAM_Prepare(void) //写液晶准备
{
TFT_wcmd(0x002C);
}


__inline void TFT_Set_Window(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
//设置寄存器值
TFT_wcmd(0x002A);
TFT_wdat(StartX>>8);
TFT_wdat(0x00FF&StartX);
TFT_wdat(EndX>>8);
TFT_wdat(0x00FF&EndX);


TFT_wcmd(0x002B);
TFT_wdat(StartY>>8);
TFT_wdat(0x00FF&StartY);
TFT_wdat(EndY>>8);
TFT_wdat(0x00FF&EndY);


TFT_wcmd(0x003A);// 16/18 bits
TFT_wdat(0x55);
TFT_wcmd(0x002C);//写液晶准备
}



/****************************************************************************
* 功能：设置屏幕座标
* 参数： X 行座标 Y 列座标
* 调用：TFT_SetCursor(50,50);
****************************************************************************/
__inline void TFT_SetCursor(u16 x, u16 y)
{
TFT_wcmd(0x002A);
TFT_wdat(x>>8);
TFT_wdat(0x00FF&x);
TFT_wdat(0x0001);
TFT_wdat(0x00DF);


TFT_wcmd(0x002B);
TFT_wdat(y>>8);
TFT_wdat(0x00FF&y);
TFT_wdat(0x0001);
TFT_wdat(0x003f);
TFT_wcmd(0x002C);//写液晶准备
}


/****************************************************************************
*功能：画点
*参数 X:0~319 Y:0~479
*说明：sendbyte(0XF800);传入此点的颜色
*调用：TFT_DrawPoint(50,50)；
*****************************************************************************/
void TFT_DrawPoint(u16 x,u16 y,u16 color)
{
TFT_SetCursor (x,y);//坐标
RS_1
CS_0
sendbyte(color);
WR_0
WR_1
CS_1
}


/****************************************************************************
*功能： 填充 设定区域 颜色
*参数： X Y 矩形坐标 color 颜色
*调用： TFT_Fill(60,60,100,100,0xF800);
****************************************************************************/
void TFT_Fill(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 color)
{
u32 i;
u32 Pixels;
Pixels=(EndX-StartX+1)*(EndY-StartY);
TFT_Set_Window(StartX,StartY,EndX,EndY);//设置窗口大小


CS_0//选择TFT
RD_1
RS_1//操作RAM
sendbyte(color);
for(i=0;i<Pixels;i++)//循环颜色
{
WR_0
WR_1
}
CS_1//释放TFT
}


/************************************************************
*功能： 画线
*参数：X Y 起点 / 终点
*调用：TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
*说明：x1,y1:起点坐标
*说明：x2,y2:终点坐标
*************************************************************/


void TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
u16 t;
int xerr=0,yerr=0,delta_x,delta_y,distance;
int incx,incy,uRow,uCol;


delta_x=x2-x1; //计算坐标增量
delta_y=y2-y1;
uRow=x1;
uCol=y1;
if(delta_x>0)incx=1; //设置单步方向
else if(delta_x==0)incx=0;//垂直线
else {incx=-1;delta_x=-delta_x;}
if(delta_y>0)incy=1;
else if(delta_y==0)incy=0;//水平线
else{incy=-1;delta_y=-delta_y;}
if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
else distance=delta_y;
for(t=0;t<=distance+1;t++ )//画线输出
{
TFT_DrawPoint(uRow,uCol,color);//画点
xerr+=delta_x ;
yerr+=delta_y ;
if(xerr>distance)
{
xerr-=distance;
uRow+=incx;
}
if(yerr>distance)
{
yerr-=distance;
uCol+=incy;
}
}
}
/**************************************************************
*功能：画矩形框
****************************************************************/
void TFT_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
TFT_DrawLine(x1,y1,x2,y1,color);
TFT_DrawLine(x1,y1,x1,y2,color);
TFT_DrawLine(x1,y2,x2,y2,color);
TFT_DrawLine(x2,y1,x2,y2,color);
}


/**************************************************************
*功能：画两个矩形框
****************************************************************/


void TFT_TwoDrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
TFT_DrawRectangle(x1, y1, x2, y2,color);//内框
TFT_DrawRectangle(x1+10, y1+10, x2-10, y2-10,color);//外框
}
/*****************************************************************
*功能：在指定位置画一个指定大小的圆
*参数：(x,y):中心点 r =半径
*******************************************************************/
void TFT_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
int a,b;
int di;
a=0;b=r;
di=3-(r<<1); //判断下个点位置的标志
while(a<=b)
{
TFT_DrawPoint(x0-b,y0-a,color);
TFT_DrawPoint(x0+b,y0-a,color);
TFT_DrawPoint(x0-a,y0+b,color);
TFT_DrawPoint(x0-b,y0-a,color);
TFT_DrawPoint(x0-a,y0-b,color);
TFT_DrawPoint(x0+b,y0+a,color);
TFT_DrawPoint(x0+a,y0-b,color);
TFT_DrawPoint(x0+a,y0+b,color);
TFT_DrawPoint(x0-b,y0+a,color);
a++;
//使用Bresenham算法画圆
if(di<0)di +=4*a+6;
else
{
di+=10+4*(a-b);
b--;
}
TFT_DrawPoint(x0+a,y0+b,color);
}
}


/****************************************************************************
竖屏
* 功 能：在指定座标范围显示一副图片
* 参数：StartX 行起始座标
* StartY 列起始座标
* EndX 行结束座标
* EndY 列结束座标
* pic 图片头指针
* 说 明：图片取模格式为水平扫描，16位颜色模式
* 调用：TFT_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void TFT_DrawPicture_s(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16*pic)
{
long int i=0;
TFT_wcmd(0x36);//屏幕文字方向
TFT_wdat(0x41);
TFT_Set_Window(StartX,StartY,EndX,EndY);
CS_0;//选择TFT
RD_1;
RS_1;//操作RAM0

for (i=0;i<((EndX)*(EndY));i++)
{
TFT_wdat(*(pic++));
WR_0 ;
WR_1;
}
CS_1;
}




/***************************************************************************
横屏
* 功 能：在指定座标范围显示一副图片
* 参数：StartX 行起始座标
* StartY 列起始座标
* EndX 行结束座标
* EndY 列结束座标
* pic 图片头指针
* 说 明：图片取模格式为水平扫描，16位颜色模式
* 调用：TFT_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void TFT_DrawPicture_h(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16*plc)
{
long int i=0;
TFT_wcmd(0x36);//屏幕文字方向
TFT_wdat(0x60);
TFT_Set_Window(StartX,StartY,EndX,EndY);
CS_0;//选择TFT
RD_1;
RS_1;//操作RAM0

for (i=0;i<((EndX)*(EndY));i++)
{
TFT_wdat(*(plc++));
WR_0 ;
WR_1;
}
CS_1;
}




/***************************************************************/


void ChineseChar(uint x,uint y,short sizex,short sizey,uint For_color,uint Bk_color,u8 *c)
{
short ncols,nrows,i,j;
ncols =sizex-1;
nrows =sizey-1;

TFT_Set_Window(x, y, x+nrows,x+ncols);
for(i=0;i<sizex*sizey/8;i++)
{
for(j=0;j<8;j++)
{
if(c[i]>>j&0x01)
TFT_wdat( For_color ); //填充字颜色
else
TFT_wdat( Bk_color); //填充背景色
}
}
}


/*****************************************************************
这是用74HC164 的重点函数
把16位数据拆分为两个八位数据 分别传输，
********************************************************************/


void sendbyte(int byte)
{
int c;
int num = (byte & 0xFF00)>>8;
int num1 = byte & 0x00FF;
for(c=0;c<8;c++)
{

digitalWrite(CLK, LOW);
digitalWrite(DAT,(num&0x80));
digitalWrite(DAT1,(num1&0x80));
digitalWrite(CLK, HIGH);
num<<=1;
num1<<=1;


}
}
/*---------------------------------------------------------------
如果字体错误横屏调节宽度 +2 ？ +4 ？
从键盘获取数字 TFT显示对应数字数组的数据
不得超过数组值
--------------------------------------------------------------------*/


int main()
{
int a;
int w,q,e,r;
wiringPiSetup() ; //初始化 树莓派 wiringPi
init_gpio(); //初始化 GPIO
TFT_init();//初始化 TFT
TFT_R61581_Clear(0x0000);//背景颜色
printf("=================\n");
printf("test\nstart....\n");
printf("=================\n");


TFT_wcmd(0x36);//屏幕文字方向
TFT_wdat(0x60); //横屏
printf("输入a\n");
scanf("%d",&a);
printf("a=%d\n",a);
fflush(stdin);
w=a/1000;
q=a%1000/100;
e=a%100/10;
r=a%10;
ChineseChar(0,0,24,16,0xFFFF,0x0000,(u8*) table[w]);
ChineseChar(10,0,24,16,0xFFFF,0x0000,(u8*) table[q]);
ChineseChar(20,0,24,16,0xFFFF,0x0000,(u8*) table[e]);
ChineseChar(30,0,24,16,0xFFFF,0x0000,(u8*) table[r]);
return 0;
}
