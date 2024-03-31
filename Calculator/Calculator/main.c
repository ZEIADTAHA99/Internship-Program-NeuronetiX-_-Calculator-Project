/*
 * Calculator.c
 *
 * Created: 21/03/2024 03:21:37 PM
 * Author : ziad
 */ 

#include <avr/io.h>
#define F_CPU 8000000ul
#include <stdio.h>
#include <util/delay.h>


// macros
#define setbit(reg,bit) reg|=(1<<bit)		// set bit 1
#define clearbit(reg,bit) reg&=~(1<<bit)	// clear bit 0
#define toggelbit(reg,bit) reg^=(1<<bit)	// toggle
#define readbit(reg,bit) ((reg>>bit)&1)		// input read

#include "lcd.h"
#include "keypad.h"



int main(void)
{
     LCD_INIT_4bit(); 
	 keypad_init(); 
	 	

    while (1) 
    {
		
		// Key-pad Pushed buttons Variables on the LCD:
		unsigned int First_number  = get_key_value();
		unsigned char operation  = get_key_value();
		unsigned int Second_number = get_key_value();
		unsigned char equal  = get_key_value();
		
		unsigned int add = First_number + Second_number;
		unsigned char add_ch[3] = {' '};
			
		unsigned int sub = First_number - Second_number;
		unsigned char sub_ch[3] = {' '};
		
		//Display the Key-pad Pushed buttons Variables on the LCD:
		LCD_send_data_4bit(First_number);
		LCD_send_data_4bit(operation);
		LCD_send_data_4bit(Second_number);
		LCD_send_data_4bit(equal);
	
	
	// For Addition Operation :
	
		for (int j = 0; j < 4; j++)
		{
			add_ch[j] = ' ';
		}
	
	if ( (operation ==  '+') && (equal ='=') )
	{
		
		Cursor_pos(0,6);
		itoa(add,add_ch,16); // Integer into ASCI
		for (int j = 0; j < 4; j++)
		{
			if(add_ch[j] < '0' || add_ch[j] > '10')
			LCD_send_data_4bit(' ');
			else
			LCD_send_command_4bit(0x80 + 0x40 + 0);// shifting cursor  to 1st  shell  of second line
			LCD_send_data_4bit(add_ch[j]);	
		}
		
	
		
	}
	
	_delay_ms(90);
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// For Subtraction Operation :
	
			for (int j =0;j<3;j++)
			{
				sub_ch[j] = ' ';
			}
			
			if ( (operation ==  '-') && (equal ='=') )
			{
				
				Cursor_pos(0,6);
				itoa(sub,sub_ch,16); // Integer into ASCI
				for (int j =0;j<3;j++)
				{
					if(sub_ch[j] < '0' || sub_ch[j] > '10')
					LCD_send_data_4bit(' ');
					else
					LCD_send_command_4bit(0x80 + 0x40 + 0);// shifting cursor  to 1st  shell  of second line
					LCD_send_data_4bit(sub_ch[j]);
				}
				
			}
			
			_delay_ms(90);
	
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////		
    }
}

