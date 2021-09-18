/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*��ݮ��ͨ��74HC164����ת����оƬ���������TFT[0��7]���ţ�IM0 = IM1 = 1;(8λ����)
*��������ǰ ����ߣ����أ�: 8��16 ChineseChar(0,0,16,8,0xF800 ,0x0001, (u8*)sz[0]);
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
int DAT1=6; //ģ�⴮�����ݷ��Ͷ�
int DAT=28; //ģ�⴮�����ݷ��Ͷ�
int CLK=29;//ģ��ʱ�ӿ��ƶ�
//TFT�ӿ�
int RD=27;//������
int WR=22;//д����
int CS=23;//Ƭѡ�͵�ƽ��Чѡ��
int RS=24;//��Ϊ��ַ ��Ϊ����
int RST=25;//��λ
int BUSY=26;//æµ���


/* LCD color */
#define White 0xFFFF //��ɫ
#define Black 0x0000 //��ɫ
#define Grey 0xF7DE //��ɫ
#define Grey1 0xDF3C //��ɫ1
#define Grey2 0xEF9E //��ɫ2
#define Gray1 0x738E //��ɫ
#define anhui 0x00CC //����ɫ
#define Blue 0x0013 //������
#define Blue2 0x051F //����
#define Blue3 0x019F //����
#define yingguang 0x7FFF //ӫ��ɫ
#define Red 0xF800 //��ɫ
#define Magenta 0xF81F //��ɫ
#define Green 0x07E0 //��ɫ
#define Cyan 0x7FFF //��ɫ
#define Yellow 0xFFE0 //��ɫ
#define GrayBlack 0x18A3 //�Һ�ɫ
#define HyalineBackColor 0x0001 // Lihao ͸������
//��ݮ��GPIO �ߵ� ����
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
void TFT_WriteRAM_Prepare(void); //дҺ��׼��
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
