#ifndef __EEPROM_H__
#define __EEPROM_H__

#include "mycommon.h"



//sfr IAP_DATA		=	0xC2;  // Flash data register
//sfr IAP_ADDRH		=	0xC3;  // Flash address HIGH
//sfr IAP_ADDRL		=	0xC4;  // Flash address LOW
//sfr IAP_CMD			=	0xC5;  // Flash command register
//sfr IAP_TRIG		=	0xC6;  // Flash command trigger
//sfr IAP_CONTR		=	0xC7;  // Flash control register 

#define CMD_IDLE		0  // Stand-by
#define CMD_READ		1  // Byte-Read
#define CMD_PROGRAM		2  // Byte-Program
#define CMD_ERASE		3  // Sector-Erase

//#define ENABLE_IAP		0x80		// if SYSCLK < 30MHz
//#define ENABLE_IAP		0x81		// if SYSCLK < 24MHz
//#define ENABLE_IAP		0x82		// if SYSCLK < 20MHz
#define ENABLE_IAP		0x83		// if SYSCLK < 12MHz
//#define ENABLE_IAP		0x84		// if SYSCLK < 6MHz
//#define ENABLE_IAP		0x85		// if SYSCLK < 3MHz
//#define ENABLE_IAP		0x86		// if SYSCLK < 2MHz
//#define ENABLE_IAP		0x87		// if SYSCLK < 1MHz

// Start and end address for STC12C5A60S2
#define IAP_ADDRESS			0x0000
#define IAP_ADDRESS_END		0x03FF

uchar IapReadByre(uint addr);
void IapWriteByte(uint addr, uchar data_temp);
void IapEraseSector(uint addr);


#endif