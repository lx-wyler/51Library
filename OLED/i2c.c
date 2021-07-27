#include "i2c.h"
#include <intrins.h>
#include "PinDefine.h"
#include "mycommon.h"

void delay7ms(void)   //7ms,误差很少
{
    unsigned char a,b;
    for(b=208;b>0;b--)
        for(a=918;a>0;a--);
}


void delay_ms(unsigned int t)  //延时的函数
{
  unsigned char i=0;

    for(;i<t;i++)
	  delay7ms();
}

void I2C_start()//开始信号
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

void I2C_stop()//停止信号
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

void I2C_send_answer()//主器件发送应答信号
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

int I2C_receive_answer()//主器件接收应答信号
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

void I2C_send_byte(unsigned char information)//向24c02发送一个字节
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

unsigned char I2C_receive_byte()//从24c02接收一个字节
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

void I2C_writedata(unsigned char slave_address,unsigned char slave_register,unsigned char information)//向24c02写一个8位数据
{
  //1st发送起始信号
  I2C_start();
	
  //2th发送从机地址和读写位
  I2C_send_byte(slave_address);
	
  //3rd接收24c02的第一个应答信号
  while(I2C_receive_answer())//==1是没有接收到应答信号
  {
    LED0=0;					 //若没有接收到应答信号，则LED0一直亮
  }
  LED0=1;
  
  //4th发送寄存器地址
  I2C_send_byte(slave_register);  
  
  //5th接收24c02的第二个应答信号
  while(I2C_receive_answer())//==1是没有接收到应答信号
  {
    LED0=0;					 //若没有接收到应答信号，则LED0一直亮
  }
  LED0=1;
  
  //6th发送要写入的数据
   I2C_send_byte(information);
  
  //7th接收24c02的第三个应答信号
  while(I2C_receive_answer())//==1是没有接收到应答信号
  {
    LED0=0;					 //若没有接收到应答信号，则LED0一直亮
  }
  LED0=1;
  
  //8th产生停止信号，结束写入
  I2C_stop();  
  
  senddelay();
}

unsigned char I2C_readdata(unsigned char slave_address,unsigned char slave_register)//从23c02读一个8位数据
{
  unsigned I2C_RX_DATA;

  //1st发送起始信号
  I2C_start();
	
  //2th发送从机地址和读写位(这里是写位)
  I2C_send_byte(slave_address);
	
  //3rd接收24c02的第一个应答信号
  while(I2C_receive_answer())//==1是没有接收到应答信号
  {
    LED0=0;					 //若没有接收到应答信号，则LED0一直亮
  }
  LED0=1;
  
  //4th发送寄存器地址
  I2C_send_byte(slave_register);  
  
  //5th接收24c02的第二个应答信号
  while(I2C_receive_answer())//==1是没有接收到应答信号
  {
    LED0=0;					 //若没有接收到应答信号，则LED0一直亮
  }
  LED0=1;
  
  //6th上面是伪写指令，下面开始读取的指令，再次发送起始信号
  I2C_start();
  
  //7th发送从机地址和读位
  I2C_send_byte(slave_address + 1);
  
  //8th接收24c02的第三个应答信号
  while(I2C_receive_answer())//==1是没有接收到应答信号
  {
    LED0=0;					 //若没有接收到应答信号，则LED0一直亮
  }
  LED0=1;
  
  //9th从24c02接收8位数据
  I2C_RX_DATA=I2C_receive_byte();
  
  //10th产生停止信号，结束读取
  I2C_stop();
  
  senddelay();
  
  return I2C_RX_DATA;
}