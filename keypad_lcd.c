#include "NXP/iolpc2148.h"
#include "delay.h"

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
#define col3 (1<<28)
void keypad_lcd_port_init (){
        PINSEL0 &= 0x0000C0FF;
        PINSEL1 &= 0xF03FFFFF;
        PINSEL2 &= 0xFFFFFF00;
        IO1DIR |= 0x000F0000;
        IO0DIR &= 0xF1FFFFFF;
        IO0DIR |= 0x0000FF70;
        
}

/*void keypad_delay(void){

      unsigned int t1,t2;
      for(t1=0;t1<300;t1++)
        for(t2=0;t2<1275;t2++);
}*/

void lcd_cmd(unsigned char command){

   IO0CLR |= (RS|RW|EN|LCD);
   IO0SET |= (command<<8);
   IO0CLR |= RS;
   IO0CLR |= RW;
   IO0SET |= EN;
   delay(2000);
   IO0CLR |= EN;
   delay(3000);
}

unsigned char keypad_output(void){
        
      unsigned char key;
      IO0CLR |= (col0|col1|col2);
      IO1CLR |= (row0|row1|row2|row3);
      
      while(1){
          IO1CLR |= row0;
          IO1SET |= (row1|row2|row3);
          
          if((IO0PIN&col0) == 0){
                key = '7';
                delay(30000);
                return key;
          }
          else if((IO0PIN&col1) == 0){
                key = '8';
                delay(30000);
                return key;
          } 
          else if((IO0PIN&col2) == 0){
                key = '9';
                delay(30000);
                return key;
          }
          else if((IO0PIN&col3) == 0){
                key = '/';
                delay(30000);
                return key;
          }
          
          
          
          IO1CLR |= row1;
          IO1SET |= (row0|row2|row3);
          
          if((IO0PIN&col0) == 0){
                key = '4';
                delay(30000);
                return key;
          }
          else if((IO0PIN&col1) == 0){
                key = '5';
                delay(30000);
                return key;
          } 
          else if((IO0PIN&col2) == 0){
                key = '6';
                delay(30000);
                return key;
          }
           else if((IO0PIN&col3) == 0){
                key = '*';
                delay(30000);
                return key;
          }
          IO1CLR |= row2;
          IO1SET |= (row0|row1|row3);
          
          if((IO0PIN&col0) == 0){
                key = '1';
                delay(30000);
                return key;
          }
          else if((IO0PIN&col1) == 0){
                key = '2';
                delay(30000);
                return key;
          } 
          else if((IO0PIN&col2) == 0){
                key = '3';
                delay(30000);
                return key;
          }
          else if((IO0PIN&col3) == 0){
                key = '-';
                delay(30000);
                return key;
          }
          
          IO1CLR |= row3;
          IO1SET |= (row0|row1|row2);
          
          if((IO0PIN&col0) == 0){
                lcd_cmd(0x01);
                delay(30000);
                return 'c';
              
          }
          else if((IO0PIN&col1) == 0){
                key = '0';
                delay(30000);
                return key;
          } 
          else if((IO0PIN&col2) == 0){
                key = '=';
                delay(30000);
                return key;
                
          }
           else if((IO0PIN&col3) == 0){
                key = '+';
                delay(30000);
                return key;
          }
         
      }

      return '\0';
      
}


/*void lcd_delay(unsigned int time){

      unsigned int n1,n2;
      for(n1=0;n1<time;n1++)
        for(n2=0;n2<1275;n2++);
}*/

void lcd_init(void){

        delay(5000);
        lcd_cmd(0x38);
        lcd_cmd(0x0f);
        lcd_cmd(0x06);
        lcd_cmd(0x01);
        delay(5000);
        lcd_cmd(0x80);
}


void lcd_dat(unsigned int data){

   IO0CLR |= (RS|RW|EN|LCD);
   IO0SET |= (data<<8);
   IO0SET |= RS;
   IO0CLR |= RW;
   IO0SET |= EN;
   delay(3000);
   IO0CLR |= EN;
   delay(3000);
}

void lcd_print(char *str){

  while(*str!='\0'){
        lcd_dat(*str);
        str++;
  }
}
