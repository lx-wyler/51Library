#ifndef __MYSTRUCT_H__
#define __MYSTRUCT_H__




#define DATA_IN_EPM_NUM	14	// ��Ҫ����eeprom�������ݵĸ���
#define ITEM_NMM		16		// �˵���ʾ��Ŀ����Ŀ��������ʾҳ������һ��
#define ITEM_VALUE_NUM	DATA_IN_EPM_NUM  // ��Ҫ��ʾ����Ŀ��ֵ����Ŀ



typedef struct Menu{
	char* item_name[ITEM_NMM];  // �� init_item_name() ������
	int* item_value[ITEM_VALUE_NUM];  // �� set_displty_item_value() ����
	int cursor_location;  // ������ʾλ��
	int cursor_input;  // ��������ʱ����λ��
	int page_max;  // ���һ��ʼ�������ݸ���������Ժ�Ͳ�����
	int cursor_line_max;  // ���ÿ�ι��λ�ñ仯��Ҫ���ݵ�ǰҳ�����¼���
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
	Controler_key key;  // ��ң�����õ��İ���
	Controler_mode ctm;  // ң������ǰ�Ŀ��Ʒ�ʽ
	Controler_operation cto;  // ��ң�����õ��Ĳ���ָ��
	
	// some robot parameter
	int gyr_xvalue;
	int gyr_yvalue;
	int gyr_zvalue;
	int acc_xvalue;
	int acc_yvalue;
	int acc_zvalue;  // 6050��ֵ
	
	// simple hand control
	int threshold_up;
	int threshold_down;
	int threshold_left;
	int threshold_right;  // ����������ֵ
	int threshold_pn_p;  // ��ˢ��������x�������󸺣������������ֵ
	int threshold_pn_n;  // ��ˢ��������x�������󸺣�����Ǹ�����ֵ
	int threshold_np_n;  // ��ѹ��������x���ȸ�����������Ǹ�����ֵ
	int threshold_np_p;  // ��ѹ��������x���ȸ������������������ֵ
	
	// some flag
	int flag_switch;  // ���� -> ������1�������ƻָ�none״̬��0�����ڼ򵥵��ü��ٶȵ�ֵ����Ϊ���ƣ����ڼ������ƺ�Ͳ����ˣ�
	int flag_lock;  // ��ˢ�������Ļ�����־�����һ����ʱ�򲻼����һ����ֵ��ctoö�ٶ�Ӧ
	
	// talk with menu
	int* data_in_eeprom[DATA_IN_EPM_NUM];  // ��Ҫ����eeprom����Ĳ���
}Robot;


#endif