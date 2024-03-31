/*
 * lcd.h
 *
 * Created: 21/03/2024 03:25:19 PM
 *  Author: ziad
 */ 


#ifndef LCD_H_
#define LCD_H_

// macros for LCd control pins:
#define RS 1
#define RW 2
#define EN 3

// Direction registers
#define LCD_Data_Dir DDRC 
#define LCD_Control_Dir DDRD
// Port registers
#define LCD_Data_Port PORTC
#define LCD_Control_Port PORTD

void LCD_INIT_4bit(void);
void LCD_send_command_4bit(unsigned char cmd);
void LCD_send_data_4bit(unsigned char data);
void LCD_send_string_4bit( char* str);
void Cursor_pos(unsigned char x_pos , unsigned char y_pos); // x_row, y_cloum


#endif /* LCD_H_ */