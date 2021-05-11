#include "PinDefine.h"
#include "ePaper.h"
#include "LED.h"
#include <math.h>
#include "mycommon.h"
#include "commonfront.h"
#include <string.h>



void reset()
{
	epaperRST=1;
	delay(150);
	
	epaperRST=0;
	delay(150);
	
	epaperRST=1;
	delay(150);
}


// 51 sends command to ePaper
void sendCom(unsigned char com){
	
	unsigned char i;
	unsigned char temp;
	
	epaperCS=0;  // enable ePaper
	epaperDC=0;  // send com
	senddelay();
	
	for(i = 0; i<8; ++i){  // first send D7
	  epaperCLK = 0;
		senddelay();
		
		temp=0x80 & com;
		if(temp == 0)
			epaperDIN=0;
		else
			epaperDIN=1;
		senddelay();
		
		epaperCLK = 1;
		com<<=1;
		senddelay();
	}  // end for
	
	epaperCS=1;
}


// 51 send date to ePaper
void sendDate(unsigned char date){
	
	unsigned char i, temp;
	
	epaperCS=0;  // enable ePaper
	epaperDC=1;  // send date
	senddelay();
	
	for(i = 0; i<8; ++i){  // first send D7
	  epaperCLK = 0;
		senddelay();
		
		temp=0x80 & date;
		//epaperDIN = ((read & com) == 1 ? 1: 0);
		if(temp == 0)
			epaperDIN=0;
		else
			epaperDIN=1;
		senddelay();
		
		epaperCLK = 1;
		date<<=1;
		senddelay();
	}  // end for
	
	epaperCS=1;
}



// 51 send date to ePaper(use this function when you want to display something)
void sendDate2(unsigned char date){
	
	unsigned char i, temp;
	
	epaperCS=0;  // enable ePaper
	epaperDC=1;  // send date
	senddelay();
	
	for(i = 0; i<8; ++i){  // first send D7
	  epaperCLK = 0;
		senddelay();
		
		temp=0x01 & date;
		if(temp == 0)
			epaperDIN=0;
		else
			epaperDIN=1;
		senddelay();
		
		epaperCLK = 1;
		date>>=1;
		senddelay();
	}  // end for
	
	epaperCS=1;
}


void lcd_chkstatus(){
  unsigned char busy;
	//LED0=0;
  do
  {
    sendCom(0x71);
		epaperBUSY=1;
		delay(2);
    busy = epaperBUSY;
    busy =!(busy & 0x01);
  }
  while(busy);   
	//LED0=1;
  delay(150);    
}


// epaper init
void ePaperInit(){
//  HRES=0x80;            //128
//  VRES_byte1=0x01;        //296
//  VRES_byte2=0x28;
	
	reset();
	
  sendCom(0x06);         //boost soft start
  sendDate (0x17);   //A
  sendDate (0x17);   //B
  sendDate (0x17);   //C       
	
  sendCom(0x04);  //Power on
  lcd_chkstatus();        //waiting for the electronic paper IC to release the idle signal
	
  sendCom(0x00);     //panel setting
  sendDate(0x17);    //LUT from OTP
  //sendDate(0x0d);    //VCOM to 0V
	
  sendCom(0x61);     //resolution setting
  sendDate (HRES);          
  sendDate (VRES_byte1);   
  sendDate (VRES_byte2);
	
	sendCom(0X50);     //VCOM AND DATA INTERVAL SETTING      
  sendDate(0x97);    //WBmode:VBDF 17|D7 VBDW 97 VBDB 57   WBRmode:VBDF F7 VBDW 77 VBDB 37  VBDR B7
}


void epaperRefresh()
{
	  LED0 = 0;
	  LED1 = 0;
    sendCom(0x12);     //DISPLAY REFRESH   
    delay(1);          //!!!The delay here is necessary, 200uS at least!!!     
    lcd_chkstatus();
	  LED0 = 1;
	  LED1 = 1;
} 


void epaperSleep()
{
    sendCom(0X50);  //VCOM AND DATA INTERVAL SETTING  
    sendDate(0xf7);
       
    sendCom(0X02);   //power off
    lcd_chkstatus();
    sendCom(0X07);   //deep sleep
    sendDate(0xA5);
}



void epaperClean()
{
    unsigned int i;
	unsigned char temp = 0xFF;
	
	  
	LED0=0;
    sendCom(0x10);        //Transfer old data
    for(i=0;i<4736;i++){
      sendDate(temp);
    }
	LED0=1;
	
	LED1=0;
    sendCom(0x13);        //Transfer new data    
    for(i=0;i<4736;i++){
      sendDate(temp);
    }
	LED1=1;
}



void epaperDisplayall()
{
    unsigned int i;
    sendCom(0x10);        //Transfer old data
    for(i=0;i<4736;i++)      
    sendDate(0xff); 
  
    sendCom(0x13);        //Transfer new data
    for(i=0;i<4736;i++)      
      ;//sendDate(gImage_1[i]);
}



//	设置局部显示的起始坐标，每次显示前都先定义一下坐标，设置的时候可以不进入局部模式
//	x是横坐标的起点，y是哪一行。横坐标终点是行尾,n是需要几个位置
//	X_MIN =< x <= X_MAX (比290大的话就无法完整显示一个字符了)
//	Y_MIN =< y <= Y_MAX
unsigned char set_par_pos6_8(unsigned int x, unsigned char y, int n){
	sendCom(0x90);
	
	if(y >= Y_MIN && y <= Y_MAX){
		sendDate(y << 3);
		sendDate(y << 3);
	}
	else
		return 0;
	
	if(x >= X_MIN && x + (6 * (n - 1)) <= X_MAX){
		sendDate((unsigned char)(x >> 8) & 0x01);
		sendDate((unsigned char)(x & 0x00ff));
		sendDate((unsigned char)(( x + (6 * n - 1 ) >> 8) & 0x01));
		sendDate((unsigned char)(( x + (6 * n - 1 )) & 0x00ff));
	}
	else
		return 0;
	// 上面这6句为什么这么写，看相应寄存器的说明，数据格式就是这样 
	
	sendDate(0x01);
	delay(1);
	
	return 1;
}



// 显示一个字符
bit Displaychar6_8(const unsigned int x, const unsigned char y, const unsigned char ch){
	int i;
	
	sendCom(0x91);  // 进入局部模式
	
	if(!set_par_pos6_8(x, y, 1))
		return 0;
	
	sendCom(0x13);        //Transfer new data
	for(i = 0; i < 6; i++)
		sendDate2(~F6x8[ch - 32][i]);  // 这里注意使用sendDate2
	epaperRefresh();

	sendCom(0x92);		//////
	return 1;
}



// 显示数字（小数，整数都行，小数固定显示2位小数）
// 在指定位置输出数字，数字长度不可超过最右端
// x: 0-要显示的开始
// y: 0-15
// num: 要显示的数字
// 数字太大的话，末位会有误差 
bit Displaynum6_8(const unsigned int x, const unsigned char y, double num){
	unsigned char N = 0;  // 记录num的位数，== 0时表示是 num == 0
	double dtemp = num;  // num备份
	long itemp = myabs(num);  // num备份
	unsigned char ctemp;  // 待显示num的某一位
	int i, j;  // 循环计数用
	bit negativeflag = 0;

	// ---判断是否是负数---
	if(num < 0)
		negativeflag = 1;
	
	// ---获得num的位数或者小数整数的位数---
	if( num == 0 )
		N = 0;
	else{
		while(itemp != 0){
			itemp /= 10;
			N++;
		}
		if(!negativeflag)
			N--;
	}
	
	// 判断剩余的位置能否够用，够用的话顺便设定局部区域
	if(isDecimal(num)){
		// 是小数
		if(x > (X_MAX - 6 * (N + 1 + 3) + 1))
			// 位置不够
			return 0;
		if(!set_par_pos6_8(x, y, N + 1 + 3))
			return 0;
	}
	else{
		// 整数
		if(x > (X_MAX - 6 * (N + 1) + 1))
			// 位置不够
			return 0;
		if(!set_par_pos6_8(x, y, N + 1))
			return 0;
	}
	
	// ---逐个显示每一位---
	itemp = myabs(num);
	
	sendCom(0x91);  // 进入局部模式
	
	sendCom(0x13);        //Transfer new data
	
	if(negativeflag){
		// 负数的话先显示一个负号
		for(j = 0; j < 6; j++)
			sendDate2(~F6x8['-' - 32][j]);  // 这里注意使用sendDate2
		N--;
	}
	
	for(i = (int)N; i >= 0; i--){
		ctemp = (unsigned char)((long)(itemp / mypow(10, i)) % 10 + 48);
		for(j = 0; j < 6; j++)
			sendDate2(~F6x8[ctemp - 32][j]);  // 这里注意使用sendDate2
	}
	
		// 小数的话需要显示后3位小数
	if(isDecimal(num)){
		dtemp = myabs(num);
		for(j = 0; j < 6; j++)
			sendDate2(~F6x8['.' - 32][j]);  // 这里注意使用sendDate2
		for(i = 0; i < 2; i++){
			ctemp = (long)(dtemp* mypow(10, i + 1))%10 + 48;
			for(j = 0; j < 6; j++)
				sendDate2(~F6x8[ctemp - 32][j]);  // 这里注意使用sendDate2
		}
	}
	
	
	epaperRefresh();
	sendCom(0x92);  // 退出局部模式
	
	return 1;
}


// 显示字符串
// 位置规定同数字，也可以看相应的set_par_pos6_8()；
void Displaystr6_8(const unsigned int x, const unsigned char y,unsigned char *ch){
	unsigned char c = 0, i = 0, j = 0;
}







