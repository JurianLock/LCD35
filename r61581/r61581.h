/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*树莓派通过74HC164串行转并行芯片输出数据至TFT[0：7]引脚；IM0 = IM1 = 1;(8位并行)
*横屏高在前 宽×高（像素）: 8×16 ChineseChar(0,0,16,8,0xF800 ,0x0001, (u8*)sz[0]);
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
#define uint unsigned int
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
//74hc164
int DAT1=6; //模拟串口数据发送端
int DAT=28; //模拟串口数据发送端
int CLK=29;//模拟时钟控制端
//TFT接口
int RD=27;//读数据
int WR=22;//写数据
int CS=23;//片选低电平有效选中
int RS=24;//低为地址 高为数据
int RST=25;//复位
int BUSY=26;//忙碌检查


/* LCD color */
#define White 0xFFFF //白色
#define Black 0x0000 //黑色
#define Grey 0xF7DE //灰色
#define Grey1 0xDF3C //灰色1
#define Grey2 0xEF9E //灰色2
#define Gray1 0x738E //灰色
#define anhui 0x00CC //暗灰色
#define Blue 0x0013 //深蓝蓝
#define Blue2 0x051F //青蓝
#define Blue3 0x019F //青蓝
#define yingguang 0x7FFF //荧光色
#define Red 0xF800 //红色
#define Magenta 0xF81F //紫色
#define Green 0x07E0 //绿色
#define Cyan 0x7FFF //青色
#define Yellow 0xFFE0 //黄色
#define GrayBlack 0x18A3 //灰黑色
#define HyalineBackColor 0x0001 // Lihao 透明背景
//树莓派GPIO 高低 控制
#define RD_0 digitalWrite(RD,LOW);
#define RD_1 digitalWrite(RD,HIGH);


#define WR_0 digitalWrite(WR,LOW);
#define WR_1 digitalWrite(WR,HIGH);


#define CS_0 digitalWrite(CS,LOW);
#define CS_1 digitalWrite(CS,HIGH);


#define RS_0 digitalWrite(RS,LOW);
#define RS_1 digitalWrite(RS,HIGH);


#define RST_0 digitalWrite(RST,LOW);
#define RST_1 digitalWrite(RST,HIGH);


#define CLK_0 digitalWrite(CLK,LOW);
#define CLK_1 digitalWrite(CLK,HIGH);




void TFT_wcmd(u16 cmd);
void TFT_wdat(u16 dat);
void TFT_init();
void TFT_back(u8 duty);
//__inline void TFT_Set_Window(u16 StartX,u16 StartY,u16 EndX,u16 EndY) ;
void TFT_Set_Window(u16 StartX,u16 StartY,u16 EndX,u16 EndY);
void sendbyte(int byte);
void init_gpio();
void TFT_WriteRAM_Prepare(void); //写液晶准备
void TFT_R61581_Clear(u16 Color);
void TFT_R61581_Clear(u16 Color);
//__inline void TFT_SetCursor(u16 x, u16 y);
void TFT_SetCursor(u16 x, u16 y);
void TFT_DrawPoint(u16 x,u16 y,u16 color);
void TFT_Fill(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 color);
void TFT_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void TFT_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void TFT_TwoDrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void TFT_Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);


void color_d(u16 color);
void TFT_DrawPicture_h(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16*plc);
void TFT_DrawPicture_s(u16 StartX,u16 StartY,u16 EndX,u16 EndY,u16 *pic);
void ChineseChar(uint x,uint y,short sizex,short sizey,uint For_color,uint Bk_color,u8 *c);
