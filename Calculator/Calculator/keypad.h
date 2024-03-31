/*
 * keypad.h
 *
 * Created: 24/03/2024 01:18:55 PM
 *  Author: ziad
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

//macros:

#define Keypad_out_dir DDRA
#define Keypad_in_dir DDRA
#define Keypad_out_port PORTA
#define Keypad_in_port PORTA
#define Keypad_in_pin PINA



// Prototype
void keypad_init(void);
unsigned int get_key_value(void);




#endif /* KEYPAD_H_ */