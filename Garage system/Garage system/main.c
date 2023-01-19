/*
 * main.c
 *
 * Created: 1/18/2023 1:48:30 PM
 *  Author: ABOALI
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "timer.h"


int main(void)
{
	unsigned char counter = 0 , flag1=1 , flag2=1,res1,res2;
	LCD_vInit();
	LCD_clearscreen();
	LCD_vSend_string("Num of cars : 0 ");
    while(1)
    {
		// For entery
		res1 = DIO_u8read('C',7);
		if(res1 == 1 && flag1 == 1 && counter < 9)
		{	    
			    flag1 =0;
				/* Increment the counter */
				counter++;
				/* Display on LCD */
				LCD_clearscreen();
				LCD_vSend_string("Num of cars : ");
				LCD_movecursor(1,15);
				LCD_vSend_char(counter+48);
				if(counter == 9)
				{
					LCD_movecursor(2,1);
					LCD_vSend_string("Garage is full");
				}
				
				/* Operate servo motor */
				timer1_wave_fastPWM_B(1) ;  // set servo shaft at 0
			    _delay_ms(1000);
			    timer1_wave_fastPWM_B(1.5) ;  // set servo shaft at 90 
				
		}
		else if (res1 == 0)
		{
			flag1 = 1;
		}   
		
        /* For exist */
		res2 = DIO_u8read('C',6);
		if(res2 == 1 && flag2 == 1 && counter > 0)
		{
			    flag2 = 0;
			    /* Decrement the counter */
			    counter --;
				/* Display on LCD */
				LCD_clearscreen();
				LCD_vSend_string("Num of cars : ");
				LCD_movecursor(1,15);
				LCD_vSend_char((counter%10)+48);
				
				if(counter == 0)
				{
					LCD_movecursor(2,1);
					LCD_vSend_string("Garage is empty");
				}
				/* Operate servo motor */
				timer1_wave_fastPWM_A(1) ;  // set servo shaft at 0
			    _delay_ms(1000);
			    timer1_wave_fastPWM_A(1.5) ;  // set servo shaft at 90
		}
		else if (res2 == 0)
		{
			flag2 = 1;
		}
    }
}
