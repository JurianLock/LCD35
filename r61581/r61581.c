/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*��ݮ��ͨ��74HC164����ת����оƬ���������TFT[0��7]���ţ�IM0 = IM1 = 1;(8λ����)
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
//GPIO��ʼ��;
//������ݮ��GPIOΪ���ģʽ
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

/****************дָ��**************
*�������ֲ�ʱ��16λ���ڣ�
****************дָ��**************/
void TFT_wcmd(u16 cmd)
{
RST_1;//ȡ����λ
RD_1;//����������
CS_1;//����Ƭѡ
CS_0;//����Ƭѡ��Ч
RS_0;//������Ϊдָ��
WR_0;//����д����
delayMicroseconds(1);
sendbyte(cmd);//����д������
delayMicroseconds(1);
WR_1;//����д����
CS_1;//�����ͷ�TFT
}

/***************д����********************
*�������ֲ�ʱ��16λ���ڣ�
***************д����********************/
void TFT_wdat(u16 dat)
{
RST_1;//ȡ����λ
RD_1;//����������
CS_1;//����Ƭѡ


CS_0;//����Ƭѡ��Ч
RS_1;//������Ϊд����
WR_0;//����д����
delayMicroseconds(1);//΢����ʱ ����� ��Ȼ TFT ���о������ػ���
sendbyte(dat);//����д������
delayMicroseconds(1);
WR_1;//����д����
CS_1;//�����ͷ�TFT
}


/*******************TFT��ʼ��************************/
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


TFT_wcmd(0x36);//��Ļ���ַ���
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
*���ܣ�TFT�������
*������ duty ռ�ձ�
*���ã� TFT_back(240)��
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
* ���ܣ�����Ļ����ָ������ɫ ����
*������Color���ֵ
* ���ã�TFT_R61581_Clear(0xffff);
****************************************************************************/
void TFT_R61581_Clear(u16 Color)
{
u32 temp;
TFT_Set_Window(0,0,319,479);
CS_0//ѡ��TFT
RD_1
RS_1//����RAM
sendbyte(Color);
for(temp=0;temp<153600;temp++)
{
WR_0
WR_1
}
CS_1//�ͷ�TFT
}


/************************************************************************
*���ܣ����ô���
*������ X Y��������
*˵�������ڴ�С:(ex-sx+1)*(ey-ex+1) ע��,ȷ��ex>=sx;ey>=sy
*���ã� TFT_Set_Window(0,0,479,319);
***********************************************************************/
void TFT_WriteRAM_Prepare(void) //дҺ��׼��
{
TFT_wcmd(0x002C);
}


__inline void TFT_Set_Window(u16 StartX,u16 StartY,u16 EndX,u16 EndY)
{
//���üĴ���ֵ
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
TFT_wcmd(0x002C);//дҺ��׼��
}



/****************************************************************************
* ���ܣ�������Ļ����
* ������ X ������ Y ������
* ���ã�TFT_SetCursor(50,50);
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
TFT_wcmd(0x002C);//дҺ��׼��
}


/****************************************************************************
*���ܣ�����
*���� X:0~319 Y:0~479
*˵����sendbyte(0XF800);����˵����ɫ
*���ã�TFT_DrawPoint(50,50)��
*****************************************************************************/
void TFT_DrawPoint(u16 x,u16 y,u16 color)
{
TFT_SetCursor (x,y);//����
RS_1
CS_0
sendbyte(color);
WR_0
WR_1
CS_1
}


/****************************************************************************
*���ܣ� ��� �趨���� ��ɫ
*������ X Y �������� color ��ɫ
*���ã� TFT_Fill(60,60,100,100,0xF800);
****************************************************************************/
void TFT_Fill(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 color)
{
u32 i;
u32 Pixels;
Pixels=(EndX-StartX+1)*(EndY-StartY);
TFT_Set_Window(StartX,StartY,EndX,EndY);//���ô��ڴ�С


CS_0//ѡ��TFT
RD_1
RS_1//����RAM
sendbyte(color);
for(i=0;i<Pixels;i++)//ѭ����ɫ
{
WR_0
WR_1
}
CS_1//�ͷ�TFT
}


/************************************************************
*���ܣ� ����
*������X Y ��� / �յ�
*���ã�TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
*˵����x1,y1:�������
*˵����x2,y2:�յ�����
*************************************************************/


void TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
u16 t;
int xerr=0,yerr=0,delta_x,delta_y,distance;
int incx,incy,uRow,uCol;


delta_x=x2-x1; //������������
delta_y=y2-y1;
uRow=x1;
uCol=y1;
if(delta_x>0)incx=1; //���õ�������
else if(delta_x==0)incx=0;//��ֱ��
else {incx=-1;delta_x=-delta_x;}
if(delta_y>0)incy=1;
else if(delta_y==0)incy=0;//ˮƽ��
else{incy=-1;delta_y=-delta_y;}
if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
else distance=delta_y;
for(t=0;t<=distance+1;t++ )//�������
{
TFT_DrawPoint(uRow,uCol,color);//����
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
*���ܣ������ο�
****************************************************************/
void TFT_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
TFT_DrawLine(x1,y1,x2,y1,color);
TFT_DrawLine(x1,y1,x1,y2,color);
TFT_DrawLine(x1,y2,x2,y2,color);
TFT_DrawLine(x2,y1,x2,y2,color);
}


/**************************************************************
*���ܣ����������ο�
****************************************************************/


void TFT_TwoDrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
TFT_DrawRectangle(x1, y1, x2, y2,color);//�ڿ�
TFT_DrawRectangle(x1+10, y1+10, x2-10, y2-10,color);//���
}
/*****************************************************************
*���ܣ���ָ��λ�û�һ��ָ����С��Բ
*������(x,y):���ĵ� r =�뾶
*******************************************************************/
void TFT_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
int a,b;
int di;
a=0;b=r;
di=3-(r<<1); //�ж��¸���λ�õı�־
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
//ʹ��Bresenham�㷨��Բ
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
����
* �� �ܣ���ָ�����귶Χ��ʾһ��ͼƬ
* ������StartX ����ʼ����
* StartY ����ʼ����
* EndX �н�������
* EndY �н�������
* pic ͼƬͷָ��
* ˵ ����ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ
* ���ã�TFT_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void TFT_DrawPicture_s(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16*pic)
{
long int i=0;
TFT_wcmd(0x36);//��Ļ���ַ���
TFT_wdat(0x41);
TFT_Set_Window(StartX,StartY,EndX,EndY);
CS_0;//ѡ��TFT
RD_1;
RS_1;//����RAM0

for (i=0;i<((EndX)*(EndY));i++)
{
TFT_wdat(*(pic++));
WR_0 ;
WR_1;
}
CS_1;
}




/***************************************************************************
����
* �� �ܣ���ָ�����귶Χ��ʾһ��ͼƬ
* ������StartX ����ʼ����
* StartY ����ʼ����
* EndX �н�������
* EndY �н�������
* pic ͼƬͷָ��
* ˵ ����ͼƬȡģ��ʽΪˮƽɨ�裬16λ��ɫģʽ
* ���ã�TFT_DrawPicture(0,0,100,100,(u16*)demo);
****************************************************************************/
void TFT_DrawPicture_h(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16*plc)
{
long int i=0;
TFT_wcmd(0x36);//��Ļ���ַ���
TFT_wdat(0x60);
TFT_Set_Window(StartX,StartY,EndX,EndY);
CS_0;//ѡ��TFT
RD_1;
RS_1;//����RAM0

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
TFT_wdat( For_color ); //�������ɫ
else
TFT_wdat( Bk_color); //��䱳��ɫ
}
}
}


/*****************************************************************
������74HC164 ���ص㺯��
��16λ���ݲ��Ϊ������λ���� �ֱ��䣬
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
����������������ڿ�� +2 �� +4 ��
�Ӽ��̻�ȡ���� TFT��ʾ��Ӧ�������������
���ó�������ֵ
--------------------------------------------------------------------*/


int main()
{
int a;
int w,q,e,r;
wiringPiSetup() ; //��ʼ�� ��ݮ�� wiringPi
init_gpio(); //��ʼ�� GPIO
TFT_init();//��ʼ�� TFT
TFT_R61581_Clear(0x0000);//������ɫ
printf("=================\n");
printf("test\nstart....\n");
printf("=================\n");


TFT_wcmd(0x36);//��Ļ���ַ���
TFT_wdat(0x60); //����
printf("����a\n");
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
