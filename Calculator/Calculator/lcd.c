/*
 * lcd.c
 *
 * Created: 21/03/2024 03:25:08 PM
 *  Author: ziad
 */ 


#include <avr/io.h>  
#include <util/delay.h>


// macros
#define setbit(reg,bit) reg|=(1<<bit)		// set bit 1
#define clearbit(reg,bit) reg&=~(1<<bit)	// clear bit 0
#define toggelbit(reg,bit) reg^=(1<<bit)	// toggle
#define readbit(reg,bit) ((reg>>bit)&1)		// input read

#include "lcd.h"


void LCD_send_command_4bit(unsigned char cmd)
{
	LCD_Data_Port = (LCD_Data_Port &0x0f) |(cmd & 0xf0);//send high nibble
	
	clearbit(LCD_Control_Port,RS);
	clearbit(LCD_Control_Port,RW);
	setbit(LCD_Control_Port,EN);// en 1
	_delay_us(1);
	clearbit(LCD_Control_Port,EN);// en 0
	_delay_us(200);// higher to lower nipple
	
	LCD_Data_Port = (LCD_Data_Port &0x0f) |(cmd<<4);//send low nibble
	setbit(LCD_Control_Port,EN);//en 1
	_delay_us(1);
	clearbit(LCD_Control_Port,EN);//en 0
	_delay_ms(1); // time command
}
void LCD_INIT_4bit(void)
{
	setbit(LCD_Data_Dir,1);
	setbit(LCD_Data_Dir,2);
	setbit(LCD_Data_Dir,3);
	
	setbit(LCD_Control_Dir,EN);
	setbit(LCD_Control_Dir,RS);
	setbit(LCD_Control_Dir,RW);
	
	
	LCD_send_command_4bit(0x02);// return home
	LCD_send_command_4bit(0x28);// 2 line  and 4 bit mode
	LCD_send_command_4bit(0x0c);// display on
	LCD_send_command_4bit(0x06);// auto increment
	LCD_send_command_4bit(0x01);// clear screen
	_delay_ms(20);
}


void LCD_send_data_4bit(unsigned char data)
{
	LCD_Data_Port = (LCD_Data_Port &0x0f) |(data & 0xf0);//send high nibble
	setbit(LCD_Control_Port,RS);// rs 1
	clearbit(LCD_Control_Port,RW);
	setbit(LCD_Control_Port,EN);//en 1
	_delay_us(1);
	clearbit(LCD_Control_Port,EN);// en 0
	_delay_us(200);
	LCD_Data_Port = (LCD_Data_Port &0x0f) |(data<<4);//send low nibble
	setbit(LCD_Control_Port,EN);
	_delay_us(1);
	clearbit(LCD_Control_Port,EN);
	_delay_ms(1);
	
}

void LCD_send_string_4bit( char* str)
{
	int count =0;
	while(str[count]!=0)
	{
		LCD_send_data_4bit(str[count]);
		count++;
	}
}

void Cursor_pos(unsigned char x_pos , unsigned char y_pos) // x_row, y_cloum
{
	uint8_t Adress = 0;
	
	if ( x_pos == 0 )
	{
		Adress = 0x80;
	}
	
	else if (x_pos == 1)
	{
		Adress = 0xC0;
	}
	
	if ( y_pos < 16 )
	{
		Adress += y_pos;
	}
	LCD_send_command_4bit(Adress);
	
}