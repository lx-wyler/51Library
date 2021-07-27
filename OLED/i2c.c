#include "i2c.h"
#include <intrins.h>
#include "PinDefine.h"
#include "mycommon.h"

void delay7ms(void)   //7ms,������
{
    unsigned char a,b;
    for(b=208;b>0;b--)
        for(a=918;a>0;a--);
}


void delay_ms(unsigned int t)  //��ʱ�ĺ���
{
  unsigned char i=0;

    for(;i<t;i++)
	  delay7ms();
}

void I2C_start()//��ʼ�ź�
{
  SDA=1;
  SCL=1;
  _nop_();
  _nop_();
  SDA=0;
  _nop_();
  _nop_();
  SCL=0;
}

void I2C_stop()//ֹͣ�ź�
{
  SDA=0;
  SCL=1;
  _nop_();
  _nop_();
  SDA=1;
  _nop_();
  _nop_();
  SCL=0;
  _nop_();
  _nop_();
}

void I2C_send_answer()//����������Ӧ���ź�
{
  SDA=0;
  SCL=0;
  _nop_();
  _nop_();
  SCL=1;
  _nop_();
  _nop_();
  SCL=0;
  _nop_();
  _nop_();
}

int I2C_receive_answer()//����������Ӧ���ź�
{
  SDA=1;
  SCL=0;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SCL=1;
  _nop_();
  _nop_();
  _nop_();
  _nop_();
  SCL=0;
  return (int)SDA;
}

void I2C_send_byte(unsigned char information)//��24c02����һ���ֽ�
{
  unsigned char i=8;

  while(i)
  {
    SCL=0;
	  
	senddelay();
	  
	if((information&0x80)==0x80)
	  {
	    SDA=1;
	  }
    else
	  {
	    SDA=0;
	  }
	  senddelay();
    SCL=1;
    _nop_();
	_nop_();
	senddelay();
	SCL=0;
	information=information<<1;
	i--;
  }
}

unsigned char I2C_receive_byte()//��24c02����һ���ֽ�
{
  unsigned char I2C_RX_DATA=0;
  int i=8;

  while(i)
  {
    SDA=1;
    SCL=0;
	_nop_();
	_nop_();
	  senddelay();
	SCL=1;
	_nop_();
	senddelay();
	if(SDA==1)
	  I2C_RX_DATA=I2C_RX_DATA|0x01;
	else
	  I2C_RX_DATA=I2C_RX_DATA|0x00;
	SCL=0;
	i--;
	if(i)
	  I2C_RX_DATA=I2C_RX_DATA<<1;
	senddelay();
  }
  return I2C_RX_DATA;
}

void I2C_writedata(unsigned char slave_address,unsigned char slave_register,unsigned char information)//��24c02дһ��8λ����
{
  //1st������ʼ�ź�
  I2C_start();
	
  //2th���ʹӻ���ַ�Ͷ�дλ
  I2C_send_byte(slave_address);
	
  //3rd����24c02�ĵ�һ��Ӧ���ź�
  while(I2C_receive_answer())//==1��û�н��յ�Ӧ���ź�
  {
    LED0=0;					 //��û�н��յ�Ӧ���źţ���LED0һֱ��
  }
  LED0=1;
  
  //4th���ͼĴ�����ַ
  I2C_send_byte(slave_register);  
  
  //5th����24c02�ĵڶ���Ӧ���ź�
  while(I2C_receive_answer())//==1��û�н��յ�Ӧ���ź�
  {
    LED0=0;					 //��û�н��յ�Ӧ���źţ���LED0һֱ��
  }
  LED0=1;
  
  //6th����Ҫд�������
   I2C_send_byte(information);
  
  //7th����24c02�ĵ�����Ӧ���ź�
  while(I2C_receive_answer())//==1��û�н��յ�Ӧ���ź�
  {
    LED0=0;					 //��û�н��յ�Ӧ���źţ���LED0һֱ��
  }
  LED0=1;
  
  //8th����ֹͣ�źţ�����д��
  I2C_stop();  
  
  senddelay();
}

unsigned char I2C_readdata(unsigned char slave_address,unsigned char slave_register)//��23c02��һ��8λ����
{
  unsigned I2C_RX_DATA;

  //1st������ʼ�ź�
  I2C_start();
	
  //2th���ʹӻ���ַ�Ͷ�дλ(������дλ)
  I2C_send_byte(slave_address);
	
  //3rd����24c02�ĵ�һ��Ӧ���ź�
  while(I2C_receive_answer())//==1��û�н��յ�Ӧ���ź�
  {
    LED0=0;					 //��û�н��յ�Ӧ���źţ���LED0һֱ��
  }
  LED0=1;
  
  //4th���ͼĴ�����ַ
  I2C_send_byte(slave_register);  
  
  //5th����24c02�ĵڶ���Ӧ���ź�
  while(I2C_receive_answer())//==1��û�н��յ�Ӧ���ź�
  {
    LED0=0;					 //��û�н��յ�Ӧ���źţ���LED0һֱ��
  }
  LED0=1;
  
  //6th������αдָ����濪ʼ��ȡ��ָ��ٴη�����ʼ�ź�
  I2C_start();
  
  //7th���ʹӻ���ַ�Ͷ�λ
  I2C_send_byte(slave_address + 1);
  
  //8th����24c02�ĵ�����Ӧ���ź�
  while(I2C_receive_answer())//==1��û�н��յ�Ӧ���ź�
  {
    LED0=0;					 //��û�н��յ�Ӧ���źţ���LED0һֱ��
  }
  LED0=1;
  
  //9th��24c02����8λ����
  I2C_RX_DATA=I2C_receive_byte();
  
  //10th����ֹͣ�źţ�������ȡ
  I2C_stop();
  
  senddelay();
  
  return I2C_RX_DATA;
}