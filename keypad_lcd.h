#include "NXP/iolpc2148.h"

#define LCD (0xFF<<8)
#define RS (1<<4)
#define RW (1<<5)
#define EN (1<<6)

#define row0 (1<<16)
#define row1 (1<<17)
#define row2 (1<<18)
#define row3 (1<<19)
#define col0 (1<<25)
#define col1 (1<<26)
#define col2 (1<<27)

void keypad_lcd_port_init ();
unsigned char keypad_output(void);
//void keypad_delay(void);

void lcd_init(void);
void lcd_cmd(unsigned char command);
void lcd_dat(unsigned int data);
void lcd_print(char *str);
//void lcd_delay(unsigned int time);
