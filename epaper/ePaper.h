#ifndef __epaper_h__
#define __epaper_h__


// epaper size define
#define HRES 0x80
#define VRES_byte1 0x01
#define VRES_byte2 0x28


// ePaper register define
#define SW_RESET	0X12
#define DRIVER_OUTPUT_CONTROL	0x01
#define DATE_ENTRY_MODE_SETTING	0X11


// epaper dimension deinfe
#define EPAPERHIGH	296
#define EPAPERWIDTH	128

// epaper partial pos limition
#define X_MIN	0
#define X_MAX	290
#define Y_MIN	0
#define Y_MAX	15

void ePaperInit();
void epaperClean();  // ˢ�ɰ�ɫ
void epaperRefresh();
void epaperSleep();
void epaperDisplayall();  // ȫ��ˢ��
bit Displaystr6_8(const unsigned int , const unsigned char ,unsigned char*);
bit Displaychar6_8(const unsigned int, const unsigned char, const unsigned char);
// ��ʾ���֣�С�����������У�С���̶���ʾ2λС����
bit Displaynum6_8(const unsigned int x, const unsigned char y, double num);
#endif