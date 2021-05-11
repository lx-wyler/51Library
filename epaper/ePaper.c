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



//	���þֲ���ʾ����ʼ���꣬ÿ����ʾǰ���ȶ���һ�����꣬���õ�ʱ����Բ�����ֲ�ģʽ
//	x�Ǻ��������㣬y����һ�С��������յ�����β,n����Ҫ����λ��
//	X_MIN =< x <= X_MAX (��290��Ļ����޷�������ʾһ���ַ���)
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
	// ������6��Ϊʲô��ôд������Ӧ�Ĵ�����˵�������ݸ�ʽ�������� 
	
	sendDate(0x01);
	delay(1);
	
	return 1;
}



// ��ʾһ���ַ�
bit Displaychar6_8(const unsigned int x, const unsigned char y, const unsigned char ch){
	int i;
	
	sendCom(0x91);  // ����ֲ�ģʽ
	
	if(!set_par_pos6_8(x, y, 1))
		return 0;
	
	sendCom(0x13);        //Transfer new data
	for(i = 0; i < 6; i++)
		sendDate2(~F6x8[ch - 32][i]);  // ����ע��ʹ��sendDate2
	epaperRefresh();

	sendCom(0x92);		//////
	return 1;
}



// ��ʾ���֣�С�����������У�С���̶���ʾ2λС����
// ��ָ��λ��������֣����ֳ��Ȳ��ɳ������Ҷ�
// x: 0-Ҫ��ʾ�Ŀ�ʼ
// y: 0-15
// num: Ҫ��ʾ������
// ����̫��Ļ���ĩλ������� 
bit Displaynum6_8(const unsigned int x, const unsigned char y, double num){
	unsigned char N = 0;  // ��¼num��λ����== 0ʱ��ʾ�� num == 0
	double dtemp = num;  // num����
	long itemp = myabs(num);  // num����
	unsigned char ctemp;  // ����ʾnum��ĳһλ
	int i, j;  // ѭ��������
	bit negativeflag = 0;

	// ---�ж��Ƿ��Ǹ���---
	if(num < 0)
		negativeflag = 1;
	
	// ---���num��λ������С��������λ��---
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
	
	// �ж�ʣ���λ���ܷ��ã����õĻ�˳���趨�ֲ�����
	if(isDecimal(num)){
		// ��С��
		if(x > (X_MAX - 6 * (N + 1 + 3) + 1))
			// λ�ò���
			return 0;
		if(!set_par_pos6_8(x, y, N + 1 + 3))
			return 0;
	}
	else{
		// ����
		if(x > (X_MAX - 6 * (N + 1) + 1))
			// λ�ò���
			return 0;
		if(!set_par_pos6_8(x, y, N + 1))
			return 0;
	}
	
	// ---�����ʾÿһλ---
	itemp = myabs(num);
	
	sendCom(0x91);  // ����ֲ�ģʽ
	
	sendCom(0x13);        //Transfer new data
	
	if(negativeflag){
		// �����Ļ�����ʾһ������
		for(j = 0; j < 6; j++)
			sendDate2(~F6x8['-' - 32][j]);  // ����ע��ʹ��sendDate2
		N--;
	}
	
	for(i = (int)N; i >= 0; i--){
		ctemp = (unsigned char)((long)(itemp / mypow(10, i)) % 10 + 48);
		for(j = 0; j < 6; j++)
			sendDate2(~F6x8[ctemp - 32][j]);  // ����ע��ʹ��sendDate2
	}
	
		// С���Ļ���Ҫ��ʾ��3λС��
	if(isDecimal(num)){
		dtemp = myabs(num);
		for(j = 0; j < 6; j++)
			sendDate2(~F6x8['.' - 32][j]);  // ����ע��ʹ��sendDate2
		for(i = 0; i < 2; i++){
			ctemp = (long)(dtemp* mypow(10, i + 1))%10 + 48;
			for(j = 0; j < 6; j++)
				sendDate2(~F6x8[ctemp - 32][j]);  // ����ע��ʹ��sendDate2
		}
	}
	
	
	epaperRefresh();
	sendCom(0x92);  // �˳��ֲ�ģʽ
	
	return 1;
}


// ��ʾ�ַ���
// λ�ù涨ͬ���֣�Ҳ���Կ���Ӧ��set_par_pos6_8()��
void Displaystr6_8(const unsigned int x, const unsigned char y,unsigned char *ch){
	unsigned char c = 0, i = 0, j = 0;
}







