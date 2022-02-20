/*
    main.c
		 Motor Interfacing with ARM7 microcontroller LPC2148
*/

#include "NXP/iolpc2148.h"
#include "system.h"
#include "keypad_lcd.h"
#include "delay.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

 char  letters[15];
 int count = 0;
 
 void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}

	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
		str[i++] = '0';

	reverse(str, i);
	str[i] = '\0';
	return i;
}
void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;

	// Extract floating part
	float fpart = n - (float)ipart;

	// convert integer part to string
	int i = intToStr(ipart, res, 0);

	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot

		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);

		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}
void clear_calc(){
  
                      lcd_cmd(0x01); 
                      lcd_cmd(0x80);
                      for(int i=0;i<15;i++)
                      letters[i] = '\0';
                      count =0;
 }
 
int char_to_numb(char c){
  
      	int x = c - '0';
        return x;
}
int main(void)
{
         //Initialize the system clock (defined in "system.c")
        clock_init();
  
        
        keypad_lcd_port_init();
        char str[8];
        int i = 0;
        lcd_init();
        lcd_print("WELCOME CALC");
        delay(5000000);
        lcd_cmd(0x01);
        lcd_cmd(0x80);
        char  letters[20];
        int count = 0;
	while(1)
	{       
                if(count <=15)
                { 
                   char c =  keypad_output();
                   if(c!='\0'&&c!='='&&c!='c'){
                   letters[count] = c;
                   lcd_dat(c);
                   count++;
                   delay(500000);
                       }
                   else if(c == 'c')
                   clear_calc();
                   else if(c == '='){
                     if(letters[0] == '*' || letters[0] == '/' || letters[0] == '+'){    
                          clear_calc();
                          lcd_print("Expression EROR");
                          clear_calc();
                          delay(500000);
                          }
                     else{   
                            letters[count] = '\0';
                                          
                              double operands[10];
                              char oprtor[10];
                              int j = 0;
                              int arrOP =0;
                              int arrOR =0;
                          
                              for(int i = 0; letters[i]!='\0';i++)
                              {      
                                if(letters[i]>=48 &&letters[i]<=57){
                                     
                                     
                                     while(letters[i]>=48 &&letters[i]<=57)
                                     { 
                                       j+=char_to_numb(letters[i]); 
                                       if(letters[i+1]>=48 &&letters[i+1]<=57)
                                         j*=10;
                                       i++;
                                     }
                                       
                                       operands[arrOP] = j;
                                       arrOP++;
                                       i--;
                                       j=0;
                                    }
                                else{
                                       oprtor[arrOR] = letters[i];
                                       arrOR++;
                                    }
                                
                              }
                     
    for(int i=0; i<arrOR; i++)
    {    
    	if(oprtor[i]== '*' || oprtor[i]=='/'){
		
    	
        	if(oprtor[i]== '*'){
			
        		operands[i] = operands[i]*operands[i+1];
        	
               }
            else if(oprtor[i]=='/'){
            	operands[i] = operands[i]/operands[i+1];
			}
		
			for(int j=i+1; j<arrOR; j++)
			{
				operands[j]=operands[j+1];
				oprtor[j-1]=oprtor[j];
			}
		      
		      arrOR--;
		      i=-1;
		}
	}

		
	for(int i=0; i<arrOR; i++){
		
		if(oprtor[i]== '+' || oprtor[i]=='-'){
		
    	
        	if(oprtor[i]== '+'){
			
        		operands[i] = operands[i]+operands[i+1];
        	
               }
            else if(oprtor[i]=='-'){
            	operands[i] = operands[i]-operands[i+1];
			}
		
			for(int j=i+1; j<arrOR; j++)
			{
				operands[j]=operands[j+1];
				oprtor[j-1]=oprtor[j];
				
			}
			 arrOR--;
	         i=-1;      	
	      }	  
	
}
                        lcd_cmd(0xc0);
                       	char res[20];
	                ftoa(operands[0], res, 3); // 3decimal digits after point                      
                        lcd_print(res);
                        count = 16; // no write
                           }
                            
                          
                                  } //end of else if(c== =)
                
                
                
                
         }//end of if
                else{
                if(keypad_output() == 'c')  
                clear_calc();
		}
                
               
        }
                return 0;
}
