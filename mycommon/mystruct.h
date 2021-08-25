#ifndef __MYSTRUCT_H__
#define __MYSTRUCT_H__




#define DATA_IN_EPM_NUM	14	// 需要存在eeprom里面数据的个数
#define ITEM_NMM		16		// 菜单显示项目的数目，加了显示页数的那一行
#define ITEM_VALUE_NUM	DATA_IN_EPM_NUM  // 需要显示的项目的值的数目



typedef struct Menu{
	char* item_name[ITEM_NMM];  // 用 init_item_name() 来构造
	int* item_value[ITEM_VALUE_NUM];  // 用 set_displty_item_value() 构造
	int cursor_location;  // 光标的显示位置
	int cursor_input;  // 输入数字时光标的位置
	int page_max;  // 这个一开始根据数据个数计算好以后就不变了
	int cursor_line_max;  // 这个每次光标位置变化都要根据当前页数重新计算
}Menu;





typedef enum Controler_key{
	key_none = 0,
	key_up,
	key_down,
	key_left,
	key_right,
	key_brush,
	key_inhale,
	key_mode,
	key_auto,
	key_stop
}Controler_key;

typedef enum Controler_operation{
	cto_none = 0,
	cto_up,
	cto_down,
	cto_left,
	cto_right,
	cto_brush,
	cto_inhale,
	cto_auto = 8,
	cto_stop
}Controler_operation;

typedef enum Controler_mode{
	mode_hand = 0,
	mode_key
}Controler_mode;

typedef struct Robot{
	Controler_key key;  // 从遥控器得到的按键
	Controler_mode ctm;  // 遥控器当前的控制方式
	Controler_operation cto;  // 从遥控器得到的操作指令
	
	// some robot parameter
	int gyr_xvalue;
	int gyr_yvalue;
	int gyr_zvalue;
	int acc_xvalue;
	int acc_yvalue;
	int acc_zvalue;  // 6050各值
	
	// simple hand control
	int threshold_up;
	int threshold_down;
	int threshold_left;
	int threshold_right;  // 上下左右阈值
	int threshold_pn_p;  // 盘刷，陀螺仪x轴先正后负，这个是正的阈值
	int threshold_pn_n;  // 盘刷，陀螺仪x轴先正后负，这个是负的阈值
	int threshold_np_n;  // 负压，陀螺仪x轴先负后正，这个是负的阈值
	int threshold_np_p;  // 负压，陀螺仪x轴先负后正，这个是正的阈值
	
	// some flag
	int flag_switch;  // 按键 -> 手势置1，待手势恢复none状态置0（现在简单的用加速度的值来作为手势，后期加入手势后就不用了）
	int flag_lock;  // 盘刷和吸附的互锁标志，检测一个的时候不检测另一个，值和cto枚举对应
	
	// talk with menu
	int* data_in_eeprom[DATA_IN_EPM_NUM];  // 需要存在eeprom里面的参数
}Robot;


#endif