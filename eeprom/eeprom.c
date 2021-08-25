#include "eeprom.h"
#include "mycommon.h"
#include <intrins.h>
#include "stc12c5a60s2.h"



// Disable ISP/IAP/EEPROM function
void IapIdle(){
	IAP_CONTR = 0;  // close iap function
	IAP_CMD = 0;  // clear command to standby
	IAP_TRIG = 0;  // clear trigger register
	IAP_ADDRH = 0x80;  // data ptr point to non-EEPROM area
	IAP_ADDRL = 0;  // clear iap address to prevent misuse
}

// Read one byte from eeprom
// Input: addr(eeprom address)
// Output: flash data
uchar IapReadByre(uint addr){
	uchar data_temp;
	
	IAP_CONTR = ENABLE_IAP;  // Open iap function and set wait time
	IAP_CMD = CMD_READ;  // set iap read command
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	
	data_temp = IAP_DATA;
	IapIdle();
	
	return data_temp;
}

// program one byte to eeprom
// Input: addr, data
void IapWriteByte(uint addr, uchar data_temp){
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_PROGRAM;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_DATA = data_temp;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	
	IapIdle();
}

// erase one sector of eeprom
void IapEraseSector(uint addr){
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_ERASE;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x5a;
	IAP_TRIG = 0xa5;
	_nop_();
	
	IapIdle();
}