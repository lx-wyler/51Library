#include "oled.h"
#include <intrins.h>
#include "mycommon.h"
#include "commonfront.h"
#include <stdio.h>
#include <string.h>



// 51 sends command to oled
void OledSendCmd(unsigned char cmd){
	
	unsigned char i;
	unsigned char temp;
	
//	epaperCS=0;  // enable ePaper
//	epaperDC=0;  // send com
	OLED_CS = 0;
	OLED_DC = 0;
	senddelay();
	
	for(i = 0; i<8; ++i){  // first send D7
//	    epaperCLK = 0;
		OLED_SCL = 0;
		senddelay();
		
		temp=0x80 & cmd;
		if(temp == 0)
//			epaperDIN=0;
			OLED_SDIN = 0;
		else
//			epaperDIN=1;
			OLED_SDIN = 1;
		senddelay();
		
//		epaperCLK = 1;
		OLED_SCL = 1;
		cmd <<= 1;
		senddelay();
	}  // end for
	
//	epaperCS=1;
	OLED_CS = 1;
}


// 51 send date to oled
void OledSendDate(unsigned char date){
	
	unsigned char i, temp;
	
//	epaperCS=0;  // enable ePaper
//	epaperDC=1;  // send date
	OLED_CS = 0;
	OLED_DC = 1;
	senddelay();
	
	for(i = 0; i<8; ++i){  // first send D7
//		epaperCLK = 0;
		OLED_SCL = 0;
		senddelay();
		
		temp=0x80 & date;
		//epaperDIN = ((read & com) == 1 ? 1: 0);
		if(temp == 0)
//			epaperDIN=0;
			OLED_SDIN = 0;
		else
//			epaperDIN=1;
			OLED_SDIN = 1;
		senddelay();
		
//		epaperCLK = 1;
		OLED_SCL = 1;
		date<<=1;
		senddelay();
	}  // end for
	
//	epaperCS=1;
	OLED_CS = 1;
}

void Oled_Set_Pos(unsigned char x, unsigned char y)
{
  OledSendCmd(0xb0+y);
  OledSendCmd((((x + 2)&0xf0)>>4)|0x10);
  OledSendCmd(((x + 2)&0x0f)); 
}

//开启OLED显示    
void OLED_Display_On(void)
{
	OledSendCmd(0X8D);  //SET DCDC命令
	OledSendCmd(0X14);  //DCDC ON
	OledSendCmd(0XAF);  //DISPLAY ON
}

//关闭OLED显示     
void OLED_Display_Off(void)
{
	OledSendCmd(0X8D);  //SET DCDC命令
	OledSendCmd(0X10);  //DCDC OFF
	OledSendCmd(0XAE);  //DISPLAY OFF
}	

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	unsigned char i, n;		    
	for(i=0;i<8;i++)  
	{  
		OledSendCmd (0xb0+i);    //设置页地址（0~7）
		OledSendCmd (0x02);      //设置显示位置—列低地址
		OledSendCmd (0x10);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
			OledSendDate(0); 
	} //更新显示
}

// 显示一组6_8字符串
void OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[])
{
	unsigned char c = 0, i = 0, j = 0;
	
	while (ch[j]!='\0'){    
		c = ch[j] - 32;
		if(x > 120){
			x = 0;
			y++;
		}
		Oled_Set_Pos(x, y);
		for(i=0;i<6;i++)
			OledSendDate(F6x8[c][i]);
		x += 6;
		j++;
	}
}
 
//显示数字
void OLED_Displaynum6_8(const unsigned int x, const unsigned char y, double num){
	unsigned char ch[21] ;
	
	sprintf(ch, "%.2f", num);
	if( isDecimal(num) )
		;
	else
		ch[strlen(ch) - 3] = '\0';
	OLED_P6x8Str(x, y, ch);
}

// 初始化OLED
void InitOled(){
	OLED_RST = 1;
	delay(100);
	OLED_RST = 0;
	delay(100);
	OLED_RST = 1;
	
	OledSendCmd(0xAE);//--turn off oled panel
	OledSendCmd(0x02);//---set low column address
	OledSendCmd(0x10);//---set high column address
	OledSendCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OledSendCmd(0x81);//--set contrast control register
	OledSendCmd(0xCF); // Set SEG Output Current Brightness
	OledSendCmd(0xA1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	OledSendCmd(0xC8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	OledSendCmd(0xA6);//--set normal display
	OledSendCmd(0xA8);//--set multiplex ratio(1 to 64)
	OledSendCmd(0x3f);//--1/64 duty
	OledSendCmd(0xD3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OledSendCmd(0x00);//-not offset
	OledSendCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OledSendCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OledSendCmd(0xD9);//--set pre-charge period
	OledSendCmd(0xF1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OledSendCmd(0xDA);//--set com pins hardware configuration
	OledSendCmd(0x12);
	OledSendCmd(0xDB);//--set vcomh
	OledSendCmd(0x40);//Set VCOM Deselect Level
	OledSendCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OledSendCmd(0x02);//
	OledSendCmd(0x8D);//--set Charge Pump enable/disable
	OledSendCmd(0x14);//--set(0x10) disable
	OledSendCmd(0xA4);// Disable Entire Display On (0xa4/0xa5)
	OledSendCmd(0xA6);// Disable Inverse Display On (0xa6/a7) 
	OledSendCmd(0xAF);//--turn on oled panel
	
	OledSendCmd(0xAF); /*display ON*/ 
	OLED_Clear();
	Oled_Set_Pos(0,0); 	
}