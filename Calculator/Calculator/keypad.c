/*
 * keypad.c
 *
 * Created: 24/03/2024 01:19:08 PM
 *  Author: ziad
 */ 



#include <avr/io.h>  // DDRA PIN PORT
#include <util/delay.h>


// macros
#define setbit(reg,bit) reg|=(1<<bit)		// set bit 1
#define clearbit(reg,bit) reg&=~(1<<bit)	// clear bit 0
#define toggelbit(reg,bit) reg^=(1<<bit)	// toggle
#define readbit(reg,bit) ((reg>>bit)&1)		// input read

#include "Keypad.h"
#include "lcd.h"


void keypad_init(void)
{
	// OUTPUT Directions Pins PORTA (DDRA)
	setbit(Keypad_out_dir,0);
	setbit(Keypad_out_dir,1);
	setbit(Keypad_out_dir,2);
	setbit(Keypad_out_dir,3);
	//INPUT Directions PINS PORTA (DDRA)
	clearbit(Keypad_in_dir,4);
	clearbit(Keypad_in_dir,5);
	clearbit(Keypad_in_dir,6);
	clearbit(Keypad_in_dir,7);
	// internal pull up resistor for input pins //
	setbit(Keypad_in_port,4);
	setbit(Keypad_in_port,5);
	setbit(Keypad_in_port,6);
	setbit(Keypad_in_port,7);

}


void output_power (int x)
{
	switch(x)
	{
		case 0:
		clearbit(Keypad_out_port,0);
		setbit(Keypad_out_port,1);
		setbit(Keypad_out_port,2);
		setbit(Keypad_out_port,3);
		break;
		case 1:
		clearbit(Keypad_out_port,1);
		setbit(Keypad_out_port,0);
		setbit(Keypad_out_port,2);
		setbit(Keypad_out_port,3);
		break;
		case 2:
		clearbit(Keypad_out_port,2);
		setbit(Keypad_out_port,1);
		setbit(Keypad_out_port,0);
		setbit(Keypad_out_port,3);
		break;
		case 3:
		clearbit(Keypad_out_port,3);
		setbit(Keypad_out_port,1);
		setbit(Keypad_out_port,0);
		setbit(Keypad_out_port,2);
		break;
		
	}
}




unsigned int get_key_value(void)

{
	unsigned int key = 1 ;
	
	while ( key == 1)
	{
		
		
		output_power(0);
		if ( readbit(Keypad_in_pin,4) == 0 ) //pull up ressitor , so LOW
		{
			key = '7';
			while(readbit(Keypad_in_pin,4)==0);// skip loop infinte
		}
		else if (readbit(Keypad_in_pin,5)==0)
		{
			key ='8';
			while(readbit(Keypad_in_pin,5)==0);
		}
		else if (readbit(Keypad_in_pin,6)==0)
		{
			key ='9';
			while(readbit(Keypad_in_pin,6)==0);
		}
		else if (readbit(Keypad_in_pin,7)==0)
		{
			key ='/';
			while(readbit(Keypad_in_pin,7)==0);
		}
		output_power(1);
		if (readbit(Keypad_in_pin,4)==0)
		{
			key ='4';
			while(readbit(Keypad_in_pin,4)==0);
		}
		else if (readbit(Keypad_in_pin,5)==0)
		{
			key ='5';
			while(readbit(Keypad_in_pin,5)==0);
		}
		else if (readbit(Keypad_in_pin,6)==0)
		{
			key ='6';
			while(readbit(Keypad_in_pin,6)==0);
		}
		else if (readbit(Keypad_in_pin,7)==0)
		{
			key ='*';
			while(readbit(Keypad_in_pin,7)==0);
		}
		output_power(2);
		if (readbit(Keypad_in_pin,4)==0)
		{
			key = '1';
			while(readbit(Keypad_in_pin,4)==0);
		}
		else if (readbit(Keypad_in_pin,5)==0)
		{
			key = '2';
			while(readbit(Keypad_in_pin,5)==0);
		}
		else if (readbit(Keypad_in_pin,6)==0)
		{
			key ='3';
			while(readbit(Keypad_in_pin,6)==0);
		}
		else if (readbit(Keypad_in_pin,7)==0)
		{
			key ='-';
			while(readbit(Keypad_in_pin,7)==0);
		}
		output_power(3);
		if (readbit(Keypad_in_pin,4)==0)
		{
			//key ='C';
			LCD_send_command_4bit(0x01);
			while(readbit(Keypad_in_pin,4)==0);
		}
		else if (readbit(Keypad_in_pin,5)==0)
		{
			key ='0';
			while(readbit(Keypad_in_pin,5)==0);
		}
		
		else if (readbit(Keypad_in_pin,6)==0)
		{
			key ='=';
			
			while(readbit(Keypad_in_pin,6)==0);
		}
		
		else if (readbit(Keypad_in_pin,7)==0)
		{
			key = '+' ;
			while(readbit(Keypad_in_pin,7)==0);
		}
	}
	return key;
}

